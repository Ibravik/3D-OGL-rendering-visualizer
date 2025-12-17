/************************************************************************/
/**
* @LC	  4/10/2016
* @file   dtShader.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2016
* @brief  dtShader class declaration. Base class for vertex or fragment shader
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <fstream>
#include <Soul_Math.h>

namespace DeveloperTest
{
	/************************************************************************/
	/* dtShader class declaration					                        */
	/************************************************************************/
	class dtShader
	{
	public:
		dtShader();		
		~dtShader();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	protected:
		char* m_ShaderBuffer;																/*!< Contain all the txt shader data */

	public:
		uint32 m_GLHandleID;																/*!< GL handle ID */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		RESULT LoadShaderSourceFile(const char* _FilePath);									/*!< Read shader source file and put it in a buffer*/		
		void OutputShaderErrorMessage();													/*!< Report error to output console */
		RESULT CompileShaderFromFile(const soString& _FilePath, uint32 _GLShaderTypeFlag);	/*!< Load and create shader */
		void ShutDown();																	/*!< Free class resources */

	public:
		RESULT StartUp(const soString& _FilePah, uint32 _GLShaderTypeFlag);					/*!< Init class */
			
	};
}