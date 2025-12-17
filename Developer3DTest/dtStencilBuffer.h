/********************************************************************/
/**
* @LC     4/11/2017
* @file   dtStencilBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017
* @brief  Declaration of class dtStencilBuffer. This can be atached to
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
	/* dtStencilBuffer class declaration				                    */
	/************************************************************************/
	class dtStencilBuffer
	{
	public:
		dtStencilBuffer();
		~dtStencilBuffer();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	public:
		uint32 m_GLHandleID;													/*!< GL buffer id */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	public:
		RESULT StartUp(const soRect& _BufferSize);	/*!< Class init from file load */
		void ShutDown();							/*!< Free the class resources */
	};
}