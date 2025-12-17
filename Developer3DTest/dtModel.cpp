/********************************************************************/
/**
* @LC	  4/7/2017
* @file   dtModel.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  dtModel class definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <GL/glew.h>
#include "dtModel.h"

/************************************************************************/
/* dtModel class definition								                */
/************************************************************************/
namespace DeveloperTest
{
	dtModel::dtModel()
	{
		m_Scene = NULL;
		m_Transform = soMath::IdentityMatrix4x4();
		m_TotalVertex = 0;
		m_TotalMesh = 0;
		m_RenderBitKey = 0;
	}

	dtModel::~dtModel()
	{
		ShutDown();
	}

	void dtModel::ShutDown()
	{
		//Delete mesh array data
		while (!m_MeshList.empty())
		{
			SAFE_DELETE(m_MeshList.back());
			m_MeshList.pop_back();
		}
	}

	RESULT dtModel::StartUp(soString _FilePath)
	{
		// Read the 3D model data
		if (FAIL(ReadFileInfo(_FilePath)))
		{
			return EC_FALSE;
		}

		printf("Load %s File Path \n", ws2s(_FilePath).c_str());

		//Mesh generation, here join all the meshes with the same material 
		for (uint32 i = 0; i < m_Scene->mNumMaterials; i++)
		{
			std::vector<aiMesh*> MaterialMesh;

			for (uint32 j = 0; j < m_Scene->mNumMeshes; j++)
			{
				if (m_Scene->mMeshes[j]->mMaterialIndex == i)
				{
					MaterialMesh.push_back(m_Scene->mMeshes[j]);
				}
			}

			// Fill all the mesh init info
			dtMesh* NewMesh = SOE_NEW dtMesh;
			MeshData _MeshData;
			_MeshData.MeshArray = &MaterialMesh;
			_MeshData.FilePath = GetFilePath(_FilePath);

			// Fill the material init info 
			MaterialData MD;
			MD.FilePath = _MeshData.FilePath;
			MD.Material = m_Scene->mMaterials[i];
			MD.Name = soString(TEXT("_Material_")) + GetFileName(_FilePath);
			_MeshData.MaterialInitData = MD;

			//Mesh generation
			if (FAIL(NewMesh->StartUp(_MeshData)))
			{
				SAFE_DELETE(NewMesh);
			}
			else
			{
				uint32 ID = (uint32)m_MeshList.size();
				NewMesh->m_MeshName = GetFileName(_FilePath) + soString(TEXT("_Mesh_")) + uint2ws(ID);

				m_MeshList.push_back(NewMesh);

				m_TotalVertex += NewMesh->m_VertexBuffer.m_VertexCount;
			}
		}
		m_TotalMesh = m_MeshList.size();

		m_Importer.FreeScene();

		printf("%s Correct \n\n", ws2s(_FilePath).c_str());
		return EC_OK;
	}

	void dtModel::Render(uint32 _ProgramID)
	{
		// Set model world matrix
		unsigned int location;

		// Set the world matrix in the vertex shader.
		location = glGetUniformLocation(_ProgramID, "WM");
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, false, &m_Transform.m00);
		}
				
		// Mesh render separately
		for (uint32 j = 0; j < m_MeshList.size(); j++)
		{
			m_MeshList.at(j)->Render(_ProgramID);
		}
	}

	RESULT dtModel::ReadFileInfo(soString _FilePath)
	{

		// Read the 3D file data
		m_Scene = m_Importer.ReadFile(ws2s(_FilePath), aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_Triangulate);
		
		// If the import failed, report it
		if (!m_Scene || m_Scene->mNumMeshes == 0)
		{
			SOE_OutputLOG("soStaticModel", "ReadFileInfo()", "Failed to read 3D model file.");
			return EC_FALSE;
		}

		return EC_OK;
	}
}