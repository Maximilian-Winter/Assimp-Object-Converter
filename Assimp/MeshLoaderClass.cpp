#include "MeshLoaderClass.h"

MeshLoaderClass::MeshLoaderClass()
{
	MeshName = "";
	SceneMeshes.clear();
	CombinedVertices.clear();
	Subsets.clear();
}

MeshLoaderClass::MeshLoaderClass(const MeshLoaderClass&)
{

}

MeshLoaderClass::~MeshLoaderClass()
{

}

bool MeshLoaderClass::LoadMeshFile(std::string FileName)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(FileName,
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_JoinIdenticalVertices |
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return false;
	}

	MeshName = FileName.substr(0, FileName.find_last_of("."));
	ProcessNodeData(scene->mRootNode, scene);
	CreateCombinedVertices();
	CalculateSubsetStarts();

	// We're done. Everything will be cleaned up by the importer destructor
	return true;

}

Vertex MeshLoaderClass::GetVerticeData(int VertexIndex)
{
	return CombinedVertices[VertexIndex];
}

int MeshLoaderClass::GetNumberOfVertices()
{
	return CombinedVertices.size();
}

SubsetType MeshLoaderClass::GetSubsetData(int SubsetIndex)
{
	return Subsets[SubsetIndex];
}

int MeshLoaderClass::GetNumberOfSubsets()
{
	return Subsets.size();
}

std::string MeshLoaderClass::GetMeshName()
{
	return MeshName;
}

void MeshLoaderClass::ProcessNodeData(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->SceneMeshes.push_back(this->ProcessMeshData(mesh, scene));
	}
	// Then do the same for each of its children
	for (int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNodeData(node->mChildren[i], scene);
	}

}

void MeshLoaderClass::CreateCombinedVertices()
{
	for (int MeshIndex = 0; MeshIndex < SceneMeshes.size(); MeshIndex++)
	{
		for (int FaceIndex = 0; FaceIndex < SceneMeshes[MeshIndex].Indices.size(); FaceIndex++)
		{
			VertexIndiceType face = SceneMeshes[MeshIndex].Indices[FaceIndex];

			for (int IndiceIndex = 0; IndiceIndex < 3; IndiceIndex++)
			{
				Vertex vertex;

				DirectX::XMFLOAT3 Pos;
				Pos.x = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].Position.x;
				Pos.y = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].Position.y;
				Pos.z = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].Position.z;
				vertex.Position = Pos;

				DirectX::XMFLOAT3 Normal;
				Normal.x = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].Normal.x;
				Normal.y = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].Normal.y;
				Normal.z = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].Normal.z;
				vertex.Normal = Normal;

				DirectX::XMFLOAT2 texCoord;
				texCoord.x = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].TexCoords.x;
				texCoord.y = SceneMeshes[MeshIndex].Vertices[face.Indices[IndiceIndex]].TexCoords.y;
				vertex.TexCoords = texCoord;
				
				// Process vertex positions, normals and texture coordinates
				CombinedVertices.push_back(vertex);
			}

		}

	}
	
}

MeshType MeshLoaderClass::ProcessMeshData(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> Vertices;
	std::vector<VertexIndiceType> Indices;
	SubsetType SubsetData;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		DirectX::XMFLOAT3 Pos;
		Pos.x = mesh->mVertices[i].x;
		Pos.y = mesh->mVertices[i].y;
		Pos.z = mesh->mVertices[i].z;
		vertex.Position = Pos;

		if (mesh->HasNormals()) // Does the mesh contain normals?
		{
			DirectX::XMFLOAT3 Normal;
			Normal.x = mesh->mNormals[i].x;
			Normal.y = mesh->mNormals[i].y;
			Normal.z = mesh->mNormals[i].z;
			vertex.Normal = Normal;
		}
		else
		{
			vertex.Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		}

		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			DirectX::XMFLOAT2 texCoord;
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = texCoord;
		}
		else
		{
			vertex.TexCoords = DirectX::XMFLOAT2(0.0f, 0.0f);
		}

		// Save vertex positions, normals and texture coordinates
		Vertices.push_back(vertex);
	}
	// Process indices

	for (int FaceIndex = 0; FaceIndex < mesh->mNumFaces; FaceIndex++)
	{
		aiFace face = mesh->mFaces[FaceIndex];
	
		if (face.mNumIndices == 3)
		{
			VertexIndiceType FaceIndices;
			FaceIndices.Indices[0] = face.mIndices[0];
			FaceIndices.Indices[1] = face.mIndices[1];
			FaceIndices.Indices[2] = face.mIndices[2];

			Indices.push_back(FaceIndices);
		}	

	}
	// Process material
	if (mesh->mMaterialIndex >= 0)
	{
		SubsetType Material;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, i, &str);
			Material.SurfaceMaterial.AlbedoMapFilename = str.C_Str();

		}

		for (int i = 0; i < material->GetTextureCount(aiTextureType_NORMALS); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_NORMALS, i, &str);
			Material.SurfaceMaterial.NormalMapFilename = str.C_Str();
		}

		int MaterialIndex = mesh->mMaterialIndex;

		std::string MaterialName = MeshName;

		if (MaterialIndex < 10)
		{
			MaterialName = MaterialName + "0" + std::to_string(MaterialIndex);
		}
		else
		{
			MaterialName = MaterialName + std::to_string(MaterialIndex);
		}

		Material.SurfaceMaterial.matName = MaterialName;
		Material.drawAmount = mesh->mNumFaces * 3;

		SubsetData = Material;
	}

	return MeshType(Vertices, Indices, SubsetData);

}

void MeshLoaderClass::CalculateSubsetStarts()
{
	for (int i = 0; i < SceneMeshes.size(); i++)
	{
		if (i == 0)
		{
			SceneMeshes[i].SubsetData.start = 0;
		}
		else
		{
			SceneMeshes[i].SubsetData.start = (SceneMeshes[i - 1].SubsetData.drawAmount - 1) + SceneMeshes[i - 1].SubsetData.start + 1;
		}

		Subsets.push_back(SceneMeshes[i].SubsetData);
	}
}