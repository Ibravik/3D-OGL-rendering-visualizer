/********************************************************************/
/**
* @LC     4/10/2017
* @file   dtRenderPass.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  Declaration of class dtRenderPass. Abstraction of pass 
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header class inclusion								                */
/************************************************************************/
#include <Soul_Math.h>
#include "dtShaderProgram.h"
#include "dtFrameBuffer.h"

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* Texture init data struct					                            */
	/************************************************************************/
	struct RenderPassData
	{
		FrameBufferData RenderTargetDataInit;		/*!< Render target initialization data */
		bool ShaderProgram;							/*!< Enable/disable shader program buffer */
		soString FSpath;							/*!< Fragment shader file path */
		soString VSpath;							/*!< Vertex shader file path */

		RenderPassData()
		{
			ShaderProgram = true;
		}
	};

	/************************************************************************/
	/* dtRenderPass class definition										*/
	/************************************************************************/
	class dtRenderPass
	{
	public:
		dtRenderPass();
		~dtRenderPass();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	public:
		dtShaderProgram m_ShaderProgram;						/*!< Fragment/Vertex shader pass */
		dtFrameBuffer m_FrameBuffer;							/*!< Render target array */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/	
	private:
		void ShutDown();										/*!< Free the class resources */

	public:
		RESULT StartUp(const RenderPassData& _Data);			/*!< Class init from file load */
		void BindPass(uint32 _BitKey, soRect* _ViewPort = NULL);/*!< Set current pass settings */
		void UnBindPass();										/*!< Set defaul settings */
		void Resize(const soRect& _BuffSize);					/*!< Resize */
	};
}