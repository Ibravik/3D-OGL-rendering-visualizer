/********************************************************************/
/**
* @LC     4/11/2017
* @file   dtFrameBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  Declaration of class dtFrameBuffer. It define a texture with
		  render info for deferred rendering
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header class inclusion								                */
/************************************************************************/
#include <Soul_Math.h>
#include "dtTexture.h"
#include "dtDepthBuffer.h"
#include "dtStencilBuffer.h"

namespace DeveloperTest
{
	/************************************************************************/
	/* Render target init data struct					                    */
	/************************************************************************/
	struct FrameBufferData
	{
		TextureData	TextureDataInit;								/*!< Texture init Params */		
		bool DepBuffer;												/*!< Enable/disable depth buffer */
		bool StencilBuffer;											/*!< Enable/disable stencil buffer */
		uint32 DeeptID;												/*!< if the deepth is diferent than 0, then assign an existing stencil */
		int32 BufferNumber;											/*!< How many textures you will create (4 max) */
		uint32 BufferID[4];											/*!< Buffer texture id, to assign an existing one */

		FrameBufferData()
		{
			DeeptID = 0;
			DepBuffer = true;
			StencilBuffer = true;
			BufferID[0] = 0;
			BufferID[1] = 0;
			BufferID[2] = 0;
			BufferID[3] = 0;
		}
	};

	/************************************************************************/
	/* dtTexture class definition											*/
	/************************************************************************/
	class dtFrameBuffer
	{
	public:
		dtFrameBuffer();
		~dtFrameBuffer();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	private:
		FrameBufferData m_FrameBufferData;								/*!< Init params for resize */		

	public:
		bool m_FrameBufferOn;											/*!< Its frame buffer on */
		bool m_ColorOn;													/*!< Its color buffer on */
		std::vector<dtTexture*> m_RenderTargetTexture;					/*!< Render target texture buffer */
		uint32 m_GLHandleID;											/*!< GL buffer id */
		dtDepthBuffer m_DepthBuffer;									/*!< DepthBuffer render target */
		
		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		void ShutDown();												/*!< Free the class resources */

	public:
		RESULT StartUp(const FrameBufferData& _RenderTargetData);		/*!< Class init */
		RESULT AddTextureTarget(const TextureData&	_TextureDataInit);	/*!< Texture init Params */
		void SetFrameBuffer(soRect* _ViewPort);							/*!< Set Render target to write */
		RESULT Resize(const soRect& _BufferSize);						/*!< Rebuild frame buffer to the new size */
	};
}

