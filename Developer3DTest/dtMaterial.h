/************************************************************************/
/**
* @LC	  4/7/2017
* @file   dtMaterial.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  Declaration of base class dtMaterial. This class manage the
		  material settings for model, in this case, only textures
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/********************************************************************/
/* Header files include					               				*/
/********************************************************************/	
#include <assimp/scene.h>
#include <Soul_Math.h>
#include "dtTexture.h"

namespace DeveloperTest
{
	/************************************************************************/
	/* MaterialData struct			                                        */
	/************************************************************************/
	struct MaterialData
	{
		aiMaterial* Material;												/*!< assipm load material info */
		soString FilePath;													/*!< Root file path */
		soString Name;														/*!< Material name */

		MaterialData()
		{
			Material = nullptr;
		}
	};

	/************************************************************************/
	/* dtMaterial declaration							    	         	*/
	/************************************************************************/
	class dtMaterial
	{
	public:
		dtMaterial();
		~dtMaterial();

		/************************************************************************/
		/* Variable										                        */
		/************************************************************************/
	public:
		soString m_MaterialName;											/*!< Material Name */
		std::vector<dtTexture*> m_TextureArray;								/*!< Array of aviliable textures */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		void ShutDown();													/*!< Free all the class resources  */
		RESULT LoadTexture(const MaterialData& _MaterialData, uint8 _MatProp);/*!< Load and create a texture buffer */

	public:
		RESULT StartUp(const MaterialData& _MaterialData);					/*!< Class init */
		void Render(uint32 _ProgramID);										/*!< Assign textures buffer */
		void EndRender();													/*!< Free texture buffer */
	};
}