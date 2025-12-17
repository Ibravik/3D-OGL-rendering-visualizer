/********************************************************************/
/**
* @LC     4/11/2017
* @file   dtDepthBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  dtDepthBuffer class definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <GL/glew.h>
#include "dtDepthBuffer.h"

/************************************************************************/
/* dtDepthBuffer declaration										    */
/************************************************************************/
namespace DeveloperTest
{
	dtDepthBuffer::dtDepthBuffer()
	{
		m_GLHandleID = 0;
	}

	dtDepthBuffer::~dtDepthBuffer()
	{
		ShutDown();
	}

	void dtDepthBuffer::ShutDown()
	{
		glDeleteRenderbuffers(1, &m_GLHandleID);
		m_GLHandleID = 0;
	}

	RESULT dtDepthBuffer::StartUp(const soRect& _BufferSize, bool _Stencil)
	{
		// The depth buffer
		glGenRenderbuffersEXT(1, &m_GLHandleID);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_GLHandleID);

		if (_Stencil)
		{
			glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8, _BufferSize.m_Width, _BufferSize.m_Height);
		}
		else
		{
			glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _BufferSize.m_Width, _BufferSize.m_Height);
		}		

		return EC_OK;
	}
}