/********************************************************************/
/**
* @LC	  4/6/2017
* @file   dtMesh.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  dtMesh class declarations
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header files inclutions								                */
/************************************************************************/
#include <GL/glew.h>
#include "dtMesh.h"

/************************************************************************/
/* dtMesh definition												    */
/************************************************************************/
namespace DeveloperTest
{
	dtMesh::dtMesh()
	{
		m_VertexArrayID = 0;
	}

	dtMesh::~dtMesh()
	{
		ShutDown();
	}

	RESULT dtMesh::StartUp(const MeshData& _MeshData)
	{
		// Allocate an OpenGL vertex array object.
		glGenVertexArrays(1, &m_VertexArrayID);

		// Bind the vertex array object to store all the buffers and vertex attributes we create here.
		glBindVertexArray(m_VertexArrayID);

		//Create the vertex and index buffer
		if (FAIL(m_IndexBuffer.StartUp(*_MeshData.MeshArray)))
		{
			return EC_FALSE;
		}

		if (FAIL(m_VertexBuffer.StartUp(*_MeshData.MeshArray)))
		{
			return EC_FALSE;
		}		

		// Create the mesh material
		m_Material.StartUp(_MeshData.MaterialInitData);

		// Unbind vertexArray
		glBindVertexArray(0);
		
		return EC_OK;
	}

	void dtMesh::ShutDown()
	{
		// Disable the two vertex array attributes.
		glDisableVertexArrayAttrib(0, m_VertexArrayID);
		glDisableVertexArrayAttrib(1, m_VertexArrayID);
		glDisableVertexArrayAttrib(2, m_VertexArrayID);

		// Release the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer.m_GLHandleID);
		glDeleteBuffers(1, &m_VertexBuffer.m_GLHandleID);

		// Release the index buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_IndexBuffer.m_GLHandleID);

		// Release the vertex array object.
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void dtMesh::Render(uint32 _ProgramID)
	{
		// Bind the texture buffers
		m_Material.Render(_ProgramID);

		// Bind the vertex array object that stored all the information about the vertex and index buffers.
		glBindVertexArray(m_VertexArrayID);
				
		// Render the vertex buffer using the index buffer.
		glDrawElements(GL_TRIANGLES, m_IndexBuffer.m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_Material.EndRender();

		// Unbind vertexArray
		glBindVertexArray(0);
	}
}