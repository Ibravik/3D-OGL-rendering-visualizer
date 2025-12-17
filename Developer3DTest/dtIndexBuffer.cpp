/********************************************************************/
/**
* @LC	  4/7/2017
* @file   dtIndexBuffer.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  dtIndexBuffer definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header files inclusion									            */
/************************************************************************/
#include <gl/glew.h>
#include "dtIndexBuffer.h"

/************************************************************************/
/* dtIndexBuffer definition								                */
/************************************************************************/
namespace DeveloperTest
{
	dtIndexBuffer::dtIndexBuffer()
	{
		m_GLHandleID = 0;
		m_IndexCount = 0;
		m_IndexList.reserve(100000);
	}

	dtIndexBuffer::~dtIndexBuffer()
	{
		ShutDown();
	}

	RESULT dtIndexBuffer::CreateMeshIndexInfo(const std::vector<aiMesh*>& MaterialMesh)
	{
		//fill index info, here we combinate all the index from diferent meshes, but same material 
		uint32 GeneralIndex = 0;
		uint32 CurrentIndex = 0;
		for (uint32 i = 0; i < static_cast<uint32>(MaterialMesh.size()); i++)
		{
			for (uint32 j = 0; j < MaterialMesh.at(i)->mNumFaces; j++)
			{
				for (uint32 k = 0; k < MaterialMesh.at(i)->mFaces[j].mNumIndices; k++)
				{
					m_IndexList.push_back(MaterialMesh.at(i)->mFaces[j].mIndices[k] + CurrentIndex);
					GeneralIndex++;
				}
			}
			CurrentIndex = GeneralIndex;
		}

		//Take the total index amount number
		m_IndexCount = m_IndexList.size();

		return EC_OK;
	}

	RESULT dtIndexBuffer::StartUp(const std::vector<aiMesh*>& _Mesh)
	{
		//load the index Data
		if (FAIL(CreateMeshIndexInfo(_Mesh)))
		{
			SOE_OutputLOG("dtIndexBuffer", "OnStartUp()", "FAIL to create index info");
			return EC_FALSE;
		}

		//Create index buffer object
		if (FAIL(CreateIndexBuffer()))
		{
			SOE_OutputLOG("dtIndexBuffer", "OnStartUp()", "FAIL to create index info");
			return EC_FALSE;
		}

		return EC_OK;
	}

	void dtIndexBuffer::ShutDown()
	{		
	}

	RESULT dtIndexBuffer::CreateIndexBuffer()
	{
		//Create index Buffer 
		glGenBuffers(1, &m_GLHandleID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLHandleID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * m_IndexList.size(), &m_IndexList[0], GL_STATIC_DRAW);

		//Release index array software data
		m_IndexList.clear();

		return EC_OK;
	}
}