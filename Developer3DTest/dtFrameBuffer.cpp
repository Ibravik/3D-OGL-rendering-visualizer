/********************************************************************/
/**
* @LC     4/11/2017
* @file   dtRenderTarget.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  dtRenderTarget class definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <GL/glew.h>
#include "dtFrameBuffer.h"

/************************************************************************/
/* dtTexture declaration											    */
/************************************************************************/
namespace DeveloperTest
{
	dtFrameBuffer::dtFrameBuffer()
	{
		m_GLHandleID = 0;
		m_ColorOn = 0;
	}
	
	dtFrameBuffer::~dtFrameBuffer()
	{
		ShutDown();
	}

	void dtFrameBuffer::ShutDown()
	{
		// Erase Textures		
		while (!m_RenderTargetTexture.empty())
		{
			SAFE_DELETE(m_RenderTargetTexture.back());
			m_RenderTargetTexture.pop_back();
		}
		
		m_DepthBuffer.ShutDown();

		glDeleteFramebuffers(1, &m_GLHandleID);

		m_GLHandleID = 0;
	}

	RESULT dtFrameBuffer::StartUp(const FrameBufferData& _RenderTargetData)
	{
		// Initialize and bind Frame buffer 
		glGenFramebuffers(1, &m_GLHandleID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_GLHandleID);

		// Create Texture array and atach to frame buffer
		for (int32 i = 0; i < _RenderTargetData.BufferNumber; i++)
		{
			if (_RenderTargetData.BufferID[i] == 0u)
			{
				dtTexture* NewTexture = SOE_NEW dtTexture;
				if (FAIL(NewTexture->StartUp(_RenderTargetData.TextureDataInit)))
				{
					SOE_OutputLOG("dtRenderTarget", "StartUp", "Render Textures creation failed");
					return EC_FALSE;
				}
				m_RenderTargetTexture.push_back(NewTexture);

				// atach Texture color Texture
				glFramebufferTexture2D(GL_FRAMEBUFFER, _RenderTargetData.TextureDataInit.AtachmentType + i, GL_TEXTURE_2D, NewTexture->m_GLHandleID, 0);
			}
			else
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, _RenderTargetData.TextureDataInit.AtachmentType + i, GL_TEXTURE_2D, _RenderTargetData.BufferID[i], 0);
			}
		}	

		// Create and atach depth buffer  to frame buffer
		if (_RenderTargetData.DepBuffer && _RenderTargetData.StencilBuffer)
		{
			if (_RenderTargetData.DeeptID == 0u)
			{
				if (FAIL(m_DepthBuffer.StartUp(_RenderTargetData.TextureDataInit.BufferSize, _RenderTargetData.StencilBuffer)))
				{
					SOE_OutputLOG("dtRenderTarget", "StartUp", "Render depth buffer creation failed");
					return EC_FALSE;
				}
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer.m_GLHandleID);
			}
			else
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RenderTargetData.DeeptID);
			}			
		}

		else if (_RenderTargetData.DepBuffer && !_RenderTargetData.StencilBuffer)
		{
			if (_RenderTargetData.DeeptID == 0u)
			{
				if (FAIL(m_DepthBuffer.StartUp(_RenderTargetData.TextureDataInit.BufferSize, _RenderTargetData.StencilBuffer)))
				{
					SOE_OutputLOG("dtRenderTarget", "StartUp", "Render depth buffer creation failed");
					return EC_FALSE;
				}
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer.m_GLHandleID);
			}
			else
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _RenderTargetData.DeeptID);
			}			
		}

		// Always check that our framebuffer is ok
		int32 Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (m_FrameBufferOn && Status != GL_FRAMEBUFFER_COMPLETE)
		{
			SOE_OutputLOG("dtRenderTarget", "StartUp", "Failed FrameBuffer creation");
			return EC_FALSE;
		}

 		m_FrameBufferData = _RenderTargetData;

		//Unbind frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return EC_OK;
	}

	RESULT dtFrameBuffer::AddTextureTarget(const TextureData& _TextureDataInit)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_GLHandleID);

		dtTexture* NewTexture = SOE_NEW dtTexture;
		if (FAIL(NewTexture->StartUp(_TextureDataInit)))
		{
			SOE_OutputLOG("dtRenderTarget", "StartUp", "Render Textures creation failed");
			return EC_FALSE;
		}
		m_RenderTargetTexture.push_back(NewTexture);

		// atach Texture color Texture
		glFramebufferTexture2D(GL_FRAMEBUFFER, _TextureDataInit.AtachmentType, GL_TEXTURE_2D, NewTexture->m_GLHandleID, 0);
		
		// Always check that our framebuffer is ok
		int32 Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (m_FrameBufferOn && Status != GL_FRAMEBUFFER_COMPLETE)
		{
			SOE_OutputLOG("dtRenderTarget", "StartUp", "Failed FrameBuffer creation");
			return EC_FALSE;
		}
		
		//Unbind frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return EC_OK;
	}

	void dtFrameBuffer::SetFrameBuffer(soRect* _ViewPort)
	{
		// Set the list of draw buffers.
		if (m_FrameBufferOn)
		{
			// Render to our framebuffer
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_GLHandleID);
		}
		else
		{
			// Render to our framebuffer
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		}

		// Render on the whole framebuffer, complete from the lower left corner to the upper right
		if (_ViewPort)
		{
			glViewport(0, 0, (GLsizei)_ViewPort->m_Width, (GLsizei)_ViewPort->m_Height);
		}
		else
		{
			glViewport(0, 0, (GLsizei)m_FrameBufferData.TextureDataInit.BufferSize.m_Width, (GLsizei)m_FrameBufferData.TextureDataInit.BufferSize.m_Height);
		}
		
		if (m_ColorOn)
		{
			GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
			glDrawBuffers(m_FrameBufferData.BufferNumber, DrawBuffers);
		}
	}

	RESULT dtFrameBuffer::Resize(const soRect& _BufferSize)
	{
		// Update size info
		m_FrameBufferData.TextureDataInit.BufferSize = _BufferSize;

		// Restart the class
		ShutDown();
		return StartUp(m_FrameBufferData);
	}

}