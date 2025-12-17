/********************************************************************/
/**
* @LC     4/11/2017
* @file   dtDepthBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  Declaration of class dtDepthBuffer. This can be atached to 
		  render target
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header class inclusion								                */
/************************************************************************/
#include <Soul_Math.h>

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* dtDepthBuffer class declaration					                    */
	/************************************************************************/
	class dtDepthBuffer
	{
	public:
		dtDepthBuffer();
		~dtDepthBuffer();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	public:
		uint32 m_GLHandleID;										/*!< GL buffer id */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	public:
		RESULT StartUp(const soRect& _BufferSize, bool _Stencil);	/*!< Class init from file load */
		void ShutDown();											/*!< Free the class resources */
	};
}