//Assimp Mesh Loader Class
//Author: Maximilian Winter


//Includes
#include <DirectXMath.h>
#include <string>
#include <vector>

//Assimp Includes
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#ifndef _MESHLOADERCLASS_H_
#define _MESHLOADERCLASS_H_


struct SurfaceMaterialData
{
	SurfaceMaterialData()
	{
		matName = "default";
		AlbedoMapFilename = "data/models/defaultAlbedo.dds";
		RoughnessMapFilename = "data/models/defaultRoughness.dds";
		MetalnessMapFilename = "data/models/defaultMetalness.dds";
		f0 = 0.06;
		RenderForward = false;
		HasNormalMap = false;
		useAlpaChannelTransparency = false;
		is_transparent = false;
	}
	std::string matName;
	std::string AlbedoMapFilename;
	std::string RoughnessMapFilename;
	std::string MetalnessMapFilename;
	std::string NormalMapFilename;
	float f0;
	bool RenderForward;
	bool useAlpaChannelTransparency;
	bool is_transparent;
	bool HasNormalMap;
};

struct Vertex 
{
	Vertex()
	{
		Position.x = 0.0;
		Position.y = 0.0;
		Position.z = 0.0;
		Normal.x = 0.0;
		Normal.y = 0.0;
		Normal.z = 0.0;
		TexCoords.x = 0.0;
		TexCoords.y = 0.0;
	}
	Vertex(DirectX::XMFLOAT3 VertexPosition, DirectX::XMFLOAT3 VertexNormal, DirectX::XMFLOAT2 VertexTexCoords)
	{
		Position = VertexPosition;
		Normal = VertexNormal;
		TexCoords = VertexTexCoords;
	}

	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT2 TexCoords;
};

struct SubsetType
{
	SurfaceMaterialData SurfaceMaterial;
	int start;
	int drawAmount;
};

struct VertexIndiceType
{
	VertexIndiceType()
	{
		Indices[0] = 0;
		Indices[1] = 0;
		Indices[2] = 0;
	}

	VertexIndiceType(int indices[3])
	{
		Indices[0] = indices[0];
		Indices[1] = indices[1];
		Indices[2] = indices[2];
	}

	int Indices[3];
};

struct MeshType
{
	MeshType(std::vector<Vertex> vertices, std::vector<VertexIndiceType> indices, SubsetType subsetData)
	{
		this->Vertices = vertices;
		this->Indices = indices;
		this->SubsetData = subsetData;
	}
	std::vector<Vertex> Vertices;
	std::vector<VertexIndiceType> Indices;
	SubsetType SubsetData;
};

class MeshLoaderClass
{
public:

	MeshLoaderClass();
	MeshLoaderClass(const MeshLoaderClass&);
	~MeshLoaderClass();

	bool LoadMeshFile(std::string FileName);

	std::string GetMeshName();

	Vertex GetVerticeData(int VerticeIndex);
	int GetNumberOfVertices();

	SubsetType GetSubsetData(int SubsetIndex);
	int GetNumberOfSubsets();

private:
	void ProcessNodeData(aiNode* node, const aiScene* scene);
	MeshType ProcessMeshData(aiMesh* mesh, const aiScene* scene);
	void CreateCombinedVertices();
	void CalculateSubsetStarts();

	std::vector<MeshType> SceneMeshes;

	std::vector<Vertex>CombinedVertices;
	std::vector<SubsetType>Subsets;

	std::string MeshName;

};
#endif 
