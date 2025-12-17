/********************************************************************/
/**
* @LC     4/11/2017
* @file   dtStencilBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  dtStencilBuffer class definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <GL/glew.h>
#include "dtStencilBuffer.h"

/************************************************************************/
/* dtStencilBuffer declaration										    */
/************************************************************************/
namespace DeveloperTest
{
	dtStencilBuffer::dtStencilBuffer()
	{
		m_GLHandleID = 0;
	}

	dtStencilBuffer::~dtStencilBuffer()
	{
		ShutDown();
	}

	void dtStencilBuffer::ShutDown()
	{
		glDeleteRenderbuffers(1, &m_GLHandleID);
		m_GLHandleID = 0;
	}

	RESULT dtStencilBuffer::StartUp(const soRect& _BufferSize)
	{
		// The stencil buffer
		glGenRenderbuffersEXT(1, &m_GLHandleID);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_GLHandleID);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX, _BufferSize.m_Width, _BufferSize.m_Height);

		return EC_OK;
	}
}