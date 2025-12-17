/************************************************************************/
/**
* @LC	  4/10/2016
* @file   dtShaderProgram.h 
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2016
* @brief  dtShaderProgram.h  class declaration. This class manage a bound 
		  of shaders
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <Soul_Math.h>
#include "dtShader.h"

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* Shader frame parameters data struct                                  */
	/************************************************************************/
	struct ShaderParameters
	{
		soMatrix4x4 VM;													/*!< Camera view matrix */
		soMatrix4x4 PM;													/*!< Camera projection */
		soMatrix4x4 RM;													/*!< Reflection Matrix */

		//Camera
		soVector3D VP;													/*!< CameraPosition*/
		float Near;														/*!< Camera near plane */
		float Far;														/*!< Camera far plane */

		//camera spot light
		float CIC;														/*!< Inner cone angle */
		float COC;														/*!< Atenuation cone angle */
		soVector3D CLP;													/*!< Light pos */
		soVector3D CLD;													/*!< Light focus dir */
		soVector4D CLC;													/*!< Light color */

		//Scenne spot light
		soVector4D SLC;													/*!< Light color */

		int32 ML;

		soMatrix4x4 SkyBoxTransform;									/*!< Sky box transform */

		float Delta;

		ShaderParameters()
		{
			RM = soMath::IdentityMatrix4x4();
			Delta = 0.0f;
		}
	};

	/************************************************************************/
	/* dtShaderProgram class declaration			                        */
	/************************************************************************/
	class dtShaderProgram
	{
	public:
		dtShaderProgram();
		~dtShaderProgram();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	private:
		dtShader m_VertexShader;													/*!< Vertex shader data */
		dtShader m_FragmentShader;													/*!< Fragmen shader data */

	public:
		uint32 m_GLHandleID;														/*!< GL handle ID */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		void OutputLinkerErrorMessage();											/*!< Report error to output console */
		void ShutDown();															/*!< Free class resources */

	public:
		RESULT StartUp(const soString& _VSFilePath, const soString& _PSFilePath);	/*!< Inicializa la clase segun las especificaciones recibidas */
		void SetShader();															/*!< Install the shader program as part of the current rendering state */
		RESULT SetShaderParameters(const ShaderParameters& _ShaderParameters);		/*!< Set the parameters to shader program */
	};
}