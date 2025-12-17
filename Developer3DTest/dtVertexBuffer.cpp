/********************************************************************/
/**
* @LC	  4/7/2017
* @file   dtVertexBuffer.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  dtVertexBuffer definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header files inclution                                               */
/************************************************************************/
#include <GL/glew.h>
#include "dtVertexBuffer.h"

/************************************************************************/
/* dtVertexBuffer definition							                */
/************************************************************************/
namespace DeveloperTest
{
	dtVertexBuffer::dtVertexBuffer()
	{
		m_GLHandleID = 0;
		m_VertexList.reserve(100000);
	}

	dtVertexBuffer::~dtVertexBuffer()
	{
		ShutDown();
	}

	RESULT dtVertexBuffer::CreateMeshVertexInfo(const std::vector<aiMesh*>& _MaterialMesh)
	{
		// Check if assimp load the info
		if (_MaterialMesh.empty())
		{
			return EC_FALSE;
		}

		// The vertex list is created from all the meshes that share the same material
		uint32 VertIndex = 0;
		uint32 InitIndex = 0;
		for (uint32 i = 0; i < static_cast<uint32>(_MaterialMesh.size()); i++)
		{
			// Fill all the vertex info
			InitIndex = VertIndex;
			aiMesh* ReadMesh = _MaterialMesh.at(i);

			for (uint32 j = 0; j < ReadMesh->mNumVertices; j++)
			{
				// Position
				Vertex NewVertex;
				NewVertex.Position.X = ReadMesh->mVertices[j].x;
				NewVertex.Position.Y = ReadMesh->mVertices[j].y;
				NewVertex.Position.Z = ReadMesh->mVertices[j].z;

				// TexCoord
				if (ReadMesh->HasTextureCoords(0))
				{
					NewVertex.TexCoord.X = ReadMesh->mTextureCoords[0][j].x;
					NewVertex.TexCoord.Y = ReadMesh->mTextureCoords[0][j].y;
				}
				else
				{
					NewVertex.TexCoord.X = 0.0f;
					NewVertex.TexCoord.Y = 0.0f;
				}

				// Normal
				if (ReadMesh->HasNormals())
				{
					NewVertex.Normal.X = ReadMesh->mNormals[j].x;
					NewVertex.Normal.Y = ReadMesh->mNormals[j].y;
					NewVertex.Normal.Z = ReadMesh->mNormals[j].z;
				}
				else
				{
					NewVertex.Normal.X = 0.0f;
					NewVertex.Normal.Y = 0.0f;
					NewVertex.Normal.Z = 0.0f;
				}

				// Binormal / tangent
				if (ReadMesh->HasTangentsAndBitangents())
				{
					NewVertex.Binormal.X = ReadMesh->mBitangents[j].x;
					NewVertex.Binormal.Y = ReadMesh->mBitangents[j].y;
					NewVertex.Binormal.Z = ReadMesh->mBitangents[j].z;

					NewVertex.Tangent.X = ReadMesh->mTangents[j].x;
					NewVertex.Tangent.Y = ReadMesh->mTangents[j].y;
					NewVertex.Tangent.Z = ReadMesh->mTangents[j].z;
				}
				else
				{
					NewVertex.Binormal.X = 0.0f;
					NewVertex.Binormal.Y = 0.0f;
					NewVertex.Binormal.Z = 0.0f;

					NewVertex.Tangent.X = 0.0f;
					NewVertex.Tangent.Y = 0.0f;
					NewVertex.Tangent.Z = 0.0f;
				}
								
				//Add the new vertex to list
				m_VertexList.push_back(NewVertex);

				VertIndex++;
			}
		}

		m_VertexCount = (uint32)m_VertexList.size();

		return EC_OK;
	}

	RESULT dtVertexBuffer::StartUp(const std::vector<aiMesh*>& _Mesh)
	{
		//Load mesh info
		if (FAIL(CreateMeshVertexInfo(_Mesh)))
		{
			SOE_OutputLOG("soVertexBuffer", "OnStartUp()", "FAIL to create Vertex array info.");
			return EC_FALSE;
		}

		//Create vertex buffer
		if (FAIL(CreateVertexBuffer()))
		{
			SOE_OutputLOG("soVertexBuffer", "OnStartUp()", "FAIL to create Vertex array info.");
			return EC_FALSE;
		}

		return EC_OK;
	}

	void dtVertexBuffer::ShutDown()
	{		
		//Delete the array software data
		m_VertexList.clear();
	}

	RESULT dtVertexBuffer::CreateVertexBuffer()
	{
		// Generate an ID for the vertex buffer.
		glGenBuffers(1, &m_GLHandleID);

		// Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_GLHandleID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * (int32)m_VertexList.size(), &m_VertexList[0], GL_STATIC_DRAW);

		// Enable the four vertex array attributes.
		glEnableVertexAttribArray(0);  // Vertex position.
		glEnableVertexAttribArray(1);  // Texture coordinates.
		glEnableVertexAttribArray(2);  // Normals.
		glEnableVertexAttribArray(3);  // Binormals.
		glEnableVertexAttribArray(4);  // Tangnt.

		// Specify the location and format of the position portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_GLHandleID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		// Specify the location and format of the texture coordinate portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_GLHandleID);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (unsigned char*)NULL + (3 * sizeof(float)));

		// Specify the location and format of the normal vector portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_GLHandleID);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (unsigned char*)NULL + (5 * sizeof(float)));

		// Specify the location and format of the binormal vector portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_GLHandleID);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (unsigned char*)NULL + (8 * sizeof(float)));

		// Specify the location and format of the tangent vector portion of the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_GLHandleID);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (unsigned char*)NULL + (11 * sizeof(float)));

		return EC_OK;
	}
}