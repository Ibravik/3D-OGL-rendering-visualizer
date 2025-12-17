/********************************************************************/
/**
* @LC     4/10/2017
* @file   dtRenderPass.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  dtRenderPass class definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include "GL/glew.h"
#include "dtRenderPass.h"

/************************************************************************/
/* dtTexture declaration											    */
/************************************************************************/
namespace DeveloperTest
{
	dtRenderPass::dtRenderPass()
	{
	}

	dtRenderPass::~dtRenderPass()
	{
	}

	RESULT dtRenderPass::StartUp(const RenderPassData& _Data)
	{
		// Load shaders
		if (_Data.ShaderProgram)
		{
			if (FAIL(m_ShaderProgram.StartUp(_Data.VSpath, _Data.FSpath)))
			{
				SOE_OutputLOG("dtRenderPass", "StartUp", "Shader program creation failed");
				return EC_FALSE;
			}
		}

		// Create Render Targets
		if (FAIL(m_FrameBuffer.StartUp(_Data.RenderTargetDataInit)))
		{
			SOE_OutputLOG("dtRenderPass", "StartUp", "Render target init failed");
			return EC_FALSE;
		}

		return EC_OK;
	}

	void dtRenderPass::BindPass(uint32 _BitKey, soRect* _ViewPort)
	{
		// Set Pass render target and shader program
		m_FrameBuffer.SetFrameBuffer(_ViewPort);
		
		// clear buffers
		if(_BitKey != 0)
			glClear(_BitKey);

		m_ShaderProgram.SetShader();
	}

	void dtRenderPass::UnBindPass()
	{
		// unbind FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// unbind shader 
		glUseProgram(0);
	}

	void dtRenderPass::Resize(const soRect& _BuffSize)
	{
		m_FrameBuffer.Resize(_BuffSize);
	}

	void dtRenderPass::ShutDown()
	{

	}

}