//Test Assimp Application
//Import Model Data
#include <iostream>
#include "MeshLoaderClass.h"
#include "ConfigDataClass.h"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision\CollisionShapes\btShapeHull.h>
#include <BulletCollision\CollisionShapes\btConvexHullShape.h>
#include <Extras\ConvexDecomposition\ConvexDecomposition.h>
#include <Extras\HACD\hacdHACD.h>

#include <LinearMath\btSerializer.h>
#include <Extras\Serialize\BulletWorldImporter\btBulletWorldImporter.h>

struct ConvexDecompositionData
{
	//keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	btAlignedObjectArray<btTriangleMesh*> m_trimeshes;
};

class MyConvexDecomposition : public ConvexDecomposition::ConvexDecompInterface
{
public:

	btAlignedObjectArray<btConvexHullShape*> m_convexShapes;
	btAlignedObjectArray<btVector3> m_convexCentroids;

	MyConvexDecomposition(ConvexDecompositionData* convexData)
		:mBaseCount(0),
		mHullCount(0),
		mConvexData(convexData)
	{
		centroid = btVector3(0, 0, 0);
	}

	virtual void ConvexDecompResult(ConvexDecomposition::ConvexResult &result)
	{


		btTriangleMesh* trimesh = new btTriangleMesh();
		mConvexData->m_trimeshes.push_back(trimesh);

		btVector3 localScaling(6.f, 6.f, 6.f);

		//calc centroid, to shift vertices around center of mass
		centroid.setValue(0, 0, 0);

		btAlignedObjectArray<btVector3> vertices;
		if (1)
		{
			//const unsigned int *src = result.mHullIndices;
			for (unsigned int i = 0; i < result.mHullVcount; i++)
			{
				btVector3 vertex(result.mHullVertices[i * 3], result.mHullVertices[i * 3 + 1], result.mHullVertices[i * 3 + 2]);
				vertex *= localScaling;
				centroid += vertex;

			}
		}

		centroid *= 1.f / (float(result.mHullVcount));

		if (1)
		{
			//const unsigned int *src = result.mHullIndices;
			for (unsigned int i = 0; i < result.mHullVcount; i++)
			{
				btVector3 vertex(result.mHullVertices[i * 3], result.mHullVertices[i * 3 + 1], result.mHullVertices[i * 3 + 2]);
				vertex *= localScaling;
				vertex -= centroid;
				vertices.push_back(vertex);
			}
		}



		if (1)
		{
			const unsigned int *src = result.mHullIndices;
			for (unsigned int i = 0; i < result.mHullTcount; i++)
			{
				unsigned int index0 = *src++;
				unsigned int index1 = *src++;
				unsigned int index2 = *src++;


				btVector3 vertex0(result.mHullVertices[index0 * 3], result.mHullVertices[index0 * 3 + 1], result.mHullVertices[index0 * 3 + 2]);
				btVector3 vertex1(result.mHullVertices[index1 * 3], result.mHullVertices[index1 * 3 + 1], result.mHullVertices[index1 * 3 + 2]);
				btVector3 vertex2(result.mHullVertices[index2 * 3], result.mHullVertices[index2 * 3 + 1], result.mHullVertices[index2 * 3 + 2]);
				vertex0 *= localScaling;
				vertex1 *= localScaling;
				vertex2 *= localScaling;

				vertex0 -= centroid;
				vertex1 -= centroid;
				vertex2 -= centroid;


				trimesh->addTriangle(vertex0, vertex1, vertex2);

				index0 += mBaseCount;
				index1 += mBaseCount;
				index2 += mBaseCount;
			}
		}

		//	float mass = 1.f;


		//this is a tools issue: due to collision margin, convex objects overlap, compensate for it here:
		//#define SHRINK_OBJECT_INWARDS 1
#ifdef SHRINK_OBJECT_INWARDS

		float collisionMargin = 0.01f;

		btAlignedObjectArray<btVector3> planeEquations;
		btGeometryUtil::getPlaneEquationsFromVertices(vertices, planeEquations);

		btAlignedObjectArray<btVector3> shiftedPlaneEquations;
		for (int p = 0; p < planeEquations.size(); p++)
		{
			btVector3 plane = planeEquations[p];
			plane[3] += collisionMargin;
			shiftedPlaneEquations.push_back(plane);
		}
		btAlignedObjectArray<btVector3> shiftedVertices;
		btGeometryUtil::getVerticesFromPlaneEquations(shiftedPlaneEquations, shiftedVertices);


		btConvexHullShape* convexShape = new btConvexHullShape(&(shiftedVertices[0].getX()), shiftedVertices.size());

#else //SHRINK_OBJECT_INWARDS

		btConvexHullShape* convexShape = new btConvexHullShape(&(vertices[0].getX()), vertices.size());
#endif 
		//if (sEnableSAT)
		//	convexShape->initializePolyhedralFeatures();
		convexShape->setMargin(0.01f);
		m_convexShapes.push_back(convexShape);
		m_convexCentroids.push_back(centroid);
		mConvexData->m_collisionShapes.push_back(convexShape);
		mBaseCount += result.mHullVcount; // advance the 'base index' counter.
	}

	int   	mBaseCount;
	int		mHullCount;
	btVector3	centroid;
	ConvexDecompositionData* mConvexData;
};

btCompoundShape* GenerateConvexDecompMesh(std::string name, std::vector<int> indicies, std::vector<float> vertices)
{
	float* verticeArr = new float[vertices.size()];
	float* IndicesArr = new float[indicies.size()];

	// Build indice array and vertex array.
	for (int i = 0; i < vertices.size(); i++)
	{
		verticeArr[i] = vertices[i];
	}

	for (int i = 0; i < indicies.size(); i++)
	{
		IndicesArr[i] = indicies[i];
	}

	// Convex decomposition.
	unsigned int depth = 5;
	float cpercent = 5;
	float ppercent = 15;
	unsigned int maxv = 16;
	float skinWidth = 0.0;

	ConvexDecomposition::DecompDesc desc;
	desc.mVcount = (vertices.size() / 3);
	desc.mVertices = verticeArr;
	desc.mTcount = (indicies.size() / 3);
	desc.mIndices = (unsigned int *)IndicesArr;
	desc.mDepth = depth;
	desc.mCpercent = cpercent;
	desc.mPpercent = ppercent;
	desc.mMaxVertices = maxv;
	desc.mSkinWidth = skinWidth;

	ConvexDecompositionData convexDecompResult;
	MyConvexDecomposition	convexDecomposition(&convexDecompResult);
	desc.mCallback = &convexDecomposition;


	//-----------------------------------------------
	// HACD
	//-----------------------------------------------

	std::vector< HACD::Vec3<HACD::Real> > points;
	std::vector< HACD::Vec3<long> > triangles;

	for (int i = 0; i< (vertices.size() / 3); i++)
	{
		int index = i * 3;
		HACD::Vec3<HACD::Real> vertex(verticeArr[index], verticeArr[index + 1], verticeArr[index + 2]);
		points.push_back(vertex);
	}

	for (int i = 0; i < (indicies.size() / 3); i++)
	{
		int index = i * 3;
		HACD::Vec3<long> triangle(IndicesArr[index], IndicesArr[index + 1], IndicesArr[index + 2]);
		triangles.push_back(triangle);
	}


	HACD::HACD myHACD;
	myHACD.SetPoints(&points[0]);
	myHACD.SetNPoints(points.size());
	myHACD.SetTriangles(&triangles[0]);
	myHACD.SetNTriangles(triangles.size());
	myHACD.SetCompacityWeight(0.1);
	myHACD.SetVolumeWeight(0.0);

	// HACD parameters
	// Recommended parameters: 2 100 0 0 0 0
	size_t nClusters = 2;
	double concavity = 100;
	bool invert = false;
	bool addExtraDistPoints = false;
	bool addNeighboursDistPoints = false;
	bool addFacesPoints = false;

	myHACD.SetNClusters(nClusters);                     // minimum number of clusters
	myHACD.SetNVerticesPerCH(100);                      // max of 100 vertices per convex-hull
	myHACD.SetConcavity(concavity);                     // maximum concavity
	myHACD.SetAddExtraDistPoints(addExtraDistPoints);
	myHACD.SetAddNeighboursDistPoints(addNeighboursDistPoints);
	myHACD.SetAddFacesPoints(addFacesPoints);

	myHACD.Compute();
	nClusters = myHACD.GetNClusters();

	std::string meshFileNameWRL = name + ".wrl";
	myHACD.Save(meshFileNameWRL.c_str(), false);

	btCompoundShape* compound = new btCompoundShape();
	//convexDecompResult.m_collisionShapes.push_back(compound);

	btTransform trans;
	trans.setIdentity();

	for (int c = 0; c<nClusters; c++)
	{
		//generate convex result
		size_t nPoints = myHACD.GetNPointsCH(c);
		size_t nTriangles = myHACD.GetNTrianglesCH(c);

		float* vertices = new float[nPoints * 3];
		unsigned int* triangles = new unsigned int[nTriangles * 3];

		HACD::Vec3<HACD::Real> * pointsCH = new HACD::Vec3<HACD::Real>[nPoints];
		HACD::Vec3<long> * trianglesCH = new HACD::Vec3<long>[nTriangles];
		myHACD.GetCH(c, pointsCH, trianglesCH);

		// points
		for (size_t v = 0; v < nPoints; v++)
		{
			vertices[3 * v] = pointsCH[v].X();
			vertices[3 * v + 1] = pointsCH[v].Y();
			vertices[3 * v + 2] = pointsCH[v].Z();
		}
		// triangles
		for (size_t f = 0; f < nTriangles; f++)
		{
			triangles[3 * f] = trianglesCH[f].X();
			triangles[3 * f + 1] = trianglesCH[f].Y();
			triangles[3 * f + 2] = trianglesCH[f].Z();
		}

		delete[] pointsCH;
		delete[] trianglesCH;

		ConvexDecomposition::ConvexResult r(nPoints, vertices, nTriangles, triangles);
		convexDecomposition.ConvexDecompResult(r);
	}

	for (int i = 0; i < convexDecomposition.m_convexShapes.size(); i++)
	{
		btVector3 centroid = convexDecomposition.m_convexCentroids[i];
		trans.setOrigin(centroid);
		btConvexHullShape* convexShape = convexDecomposition.m_convexShapes[i];

		compound->addChildShape(trans, convexShape);
		//btRigidBody* body;
		//body = localCreateRigidBody(1.0, trans, convexShape);
		/*
		btMotionState* motion = new btDefaultMotionState(trans);

		btVector3 inertia(0, 0, 0);

		convexShape->calculateLocalInertia(1.0f, inertia);

		btRigidBody::btRigidBodyConstructionInfo info(btScalar(mass), motion, convexShape, inertia);
		btRigidBody* body = new btRigidBody(info);
		m_dynamicsWorld->addRigidBody(body);*/
	}

	compound->setLocalScaling(btVector3(0.168, 0.168, 0.168));
	compound->recalculateLocalAabb();

	delete verticeArr;
	delete IndicesArr;

	return compound;
}


void printEndLine(float lines)
{
	for (int i = 0; i < lines; i++)
	{
		std::cout << std::endl;
	}
}

void printValueToConsole(std::string valHeader, int val)
{
	std::cout << "  " << valHeader << ": " << val << std::endl;
}

void printValueToConsole(std::string valHeader, bool val)
{
	std::cout << "  " << valHeader << ": " << val << std::endl;
}

void printValueToConsole(std::string valHeader, float val)
{
	std::cout << "  " << valHeader << ": " << val << std::endl;
}

void printValueToConsole(std::string valHeader, std::string val)
{
	std::cout << "  " << valHeader << ": " << val << std::endl;
}

void printValueToConsole(std::string valHeader, Vertex val)
{
	std::cout << "  " << valHeader << " Position X: " << val.Position.x << std::endl;
	std::cout << "  " << valHeader << " Position Y: " << val.Position.y << std::endl;
	std::cout << "  " << valHeader << " Position Z: " << val.Position.z << std::endl;

	std::cout << "  " << valHeader << " Normal X: " << val.Normal.x << std::endl;
	std::cout << "  " << valHeader << " Normal Y: " << val.Normal.y << std::endl;
	std::cout << "  " << valHeader << " Normal Z: " << val.Normal.z << std::endl;

	std::cout << "  " << valHeader << " TexCoord X: " << val.TexCoords.x << std::endl;
	std::cout << "  " << valHeader << " TexCoord Y: " << val.TexCoords.y << std::endl;
}

void printValueToConsole(std::string valHeader, SubsetType val)
{
	std::cout << "  " << valHeader << " Material Name: " << val.SurfaceMaterial.matName << std::endl;
	std::cout << "  " << valHeader << " Start: " << val.start << std::endl;
	std::cout << "  " << valHeader << " Draw Amount: " << val.drawAmount << std::endl;
	std::cout << "  " << valHeader << " Albedo Map: " << val.SurfaceMaterial.AlbedoMapFilename << std::endl;
	std::cout << "  " << valHeader << " Roughness Map: " << val.SurfaceMaterial.RoughnessMapFilename << std::endl;
	std::cout << "  " << valHeader << " Metalness Map: " << val.SurfaceMaterial.MetalnessMapFilename << std::endl;
	std::cout << "  " << valHeader << " f0: " << val.SurfaceMaterial.f0 << std::endl;
	std::cout << "  " << valHeader << " Has normal map : " << val.SurfaceMaterial.HasNormalMap << std::endl;
	std::cout << "  " << valHeader << " render_forward : " << val.SurfaceMaterial.RenderForward << std::endl;

	printEndLine(2);
}

void printVerticesFromVectorToConsole(std::string valHeader, std::vector<float> &val)
{
	int vertexcount = val.size() / 8;
	Vertex vertices;

	for (int k = 0; k < val.size(); k++)
	{
		std::cout << " " << val[k] << " " << val[k + 1] << " " << val[k + 2] << " " << val[k + 3]
			<< " " << val[k + 4] << " " << val[k + 5] << " " << val[k + 6] << " " << val[k + 7] << std::endl;
		std::cout << std::endl;

		k += 7;
	}
}


void main()
{
	bool result;
	std::string MeshFilename;

	std::cout << "Geben Sie den Dateinamen des umzuwandelnen Model ein: ";
	std::cin >> MeshFilename;

	MeshLoaderClass MeshLoader;
	
	// Load in the model file with the assimp libary.
	result = MeshLoader.LoadMeshFile(MeshFilename);

	// Check if the model is loaded correctly and proced, return an error message if not.
	if (result)
	{
		printEndLine(2);
		std::cout << "Mesh erfolgreich geladen." << std::endl;

		char createCollisionMesh;

		printEndLine(2);
		std::cout << "HACD Collision Mesh erstellen? (ja = j, nein = n) : " << std::flush;

		std::cin >> createCollisionMesh;

		// Create the output files for the mesh and material data.
		ConfigDataClass MeshOutputFile;
		ConfigDataClass MaterialOutputFile;
		MaterialOutputFile.ClearConfigData();
		MeshOutputFile.ClearConfigData();

		std::vector<float> MeshVertices;

		std::vector<int> indicies;
		std::vector<float> verticePositions;

		std::string MeshOutputFilename = MeshLoader.GetMeshName() + ".smo";
		std::string MaterialOutputFilename = MeshLoader.GetMeshName() + ".matlib";
		std::string CollisionMeshOutputFilename = MeshLoader.GetMeshName() + ".bcs";

		// Add general mesh infos to the output file.
		MeshOutputFile.AddStringValueByName("Mesh", "Material_Libary", "data/models/" + MaterialOutputFilename);
		if (createCollisionMesh == 'j')
		{
			MeshOutputFile.AddStringValueByName("Mesh", "Collision_Mesh_File", "data/models/" + CollisionMeshOutputFilename);
		}
		MeshOutputFile.AddIntValueByName("Mesh", "Vertex_Count", MeshLoader.GetNumberOfVertices());
		MeshOutputFile.AddIntValueByName("Mesh", "Subset_Count", MeshLoader.GetNumberOfSubsets());

		// Add the subset and material data to the file.
		for (int i = 0; i < MeshLoader.GetNumberOfSubsets(); i++)
		{
			SubsetType TempSubset = MeshLoader.GetSubsetData(i);

			std::string MeshSection = "Mesh_Subset" + std::to_string(i);

			MeshOutputFile.AddIntValueByName(MeshSection, "Subset_Start", TempSubset.start);
			MeshOutputFile.AddIntValueByName(MeshSection, "Subset_Draw_Amount", TempSubset.drawAmount);
			MeshOutputFile.AddStringValueByName(MeshSection, "Subset_Material_Name", TempSubset.SurfaceMaterial.matName);

			MaterialOutputFile.AddBoolValueByName(TempSubset.SurfaceMaterial.matName, "render_forward", TempSubset.SurfaceMaterial.RenderForward);
			MaterialOutputFile.AddBoolValueByName(TempSubset.SurfaceMaterial.matName, "is_transparent", TempSubset.SurfaceMaterial.is_transparent);
			MaterialOutputFile.AddBoolValueByName(TempSubset.SurfaceMaterial.matName, "use_alphachannel_transparency", TempSubset.SurfaceMaterial.useAlpaChannelTransparency);
			MaterialOutputFile.AddStringValueByName(TempSubset.SurfaceMaterial.matName, "albedo_map", TempSubset.SurfaceMaterial.AlbedoMapFilename);
			MaterialOutputFile.AddStringValueByName(TempSubset.SurfaceMaterial.matName, "roughness_map", TempSubset.SurfaceMaterial.RoughnessMapFilename);
			MaterialOutputFile.AddStringValueByName(TempSubset.SurfaceMaterial.matName, "metalness_map", TempSubset.SurfaceMaterial.MetalnessMapFilename);
			MaterialOutputFile.AddStringValueByName(TempSubset.SurfaceMaterial.matName, "normal_map", TempSubset.SurfaceMaterial.NormalMapFilename);
			MaterialOutputFile.AddFloatValueByName(TempSubset.SurfaceMaterial.matName, "f0", TempSubset.SurfaceMaterial.f0);


			
		}

		/* Creat a single float vector for the mesh vertices in the form of:
		
			position X,y,z uv coordinates x,y and normal x,y,z

		*/

		for (int i = 0; i < MeshLoader.GetNumberOfVertices(); i++)
		{
			Vertex TempVertex = MeshLoader.GetVerticeData(i);

			MeshVertices.push_back(TempVertex.Position.x);
			MeshVertices.push_back(TempVertex.Position.y);
			MeshVertices.push_back(TempVertex.Position.z);

			verticePositions.push_back(TempVertex.Position.x);
			verticePositions.push_back(TempVertex.Position.y);
			verticePositions.push_back(TempVertex.Position.z);

			MeshVertices.push_back(TempVertex.TexCoords.x);
			MeshVertices.push_back(TempVertex.TexCoords.y);

			MeshVertices.push_back(TempVertex.Normal.x);
			MeshVertices.push_back(TempVertex.Normal.y);
			MeshVertices.push_back(TempVertex.Normal.z);
		}

		for (int i = 0; i < MeshLoader.GetNumberOfVertices(); i++)
		{
			indicies.push_back(i);
		}

		// Add the mesh vertices to the mesh output file.
		MeshOutputFile.AddFloatVectorByName("Mesh", "Vertices", MeshVertices);
		
		if (createCollisionMesh == 'j')
		{
			printEndLine(2);
			std::cout << "Erstelle Collision Mesh." << std::endl;
			std::cout << "Dies kann einige Minuten in Anspruch nehmen.... " << std::endl;

			// Erstelle convex decomposition mesh.
			btCompoundShape* mesh = GenerateConvexDecompMesh(MeshLoader.GetMeshName(), indicies, verticePositions);

			// Speichere convex decomposition mesh
			btDefaultSerializer* serializer = new btDefaultSerializer();

			serializer->startSerialization();
			mesh->serializeSingleShape(serializer);
			serializer->finishSerialization();

			FILE* file;
			fopen_s(&file, CollisionMeshOutputFilename.c_str(), "wb");
			fwrite(serializer->getBufferPointer(), serializer->getCurrentBufferSize(), 1, file);
			fclose(file);

			// Free up used memory
			delete mesh;
			delete serializer;

		}

		MeshOutputFile.SaveConfigDataFile(MeshOutputFilename, "SMO Converter Mesh File");
		MaterialOutputFile.SaveConfigDataFile(MaterialOutputFilename, "SMO Converter Material File");
	
		printEndLine(2);
		std::cout << "Mesh Konvertierung abgeschlossen." << std::endl;

		
	}
	else
	{
		std::cout << "Datei nicht gefunden." << std::endl;
	}

	system("pause");

}
