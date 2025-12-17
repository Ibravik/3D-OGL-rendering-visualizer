/********************************************************************/
/**
* @LC	  4/7/2017
* @file   dtModel.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  dtModel class declaration. It contain all the info for each
		  model in scenne
* @bug	   No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <assimp/Importer.hpp>								/*!< C++ importer interface */
#include <assimp/scene.h>									/*!< Output data structure */
#include <assimp/postprocess.h>								/*!< Post processing flags */
#include <Soul_Math.h>										/*!< Math functions and defines */
#include "dtMesh.h"											/*!< Mesh info */

namespace DeveloperTest
{
	/************************************************************************/
	/* dtModel class declaration											*/
	/************************************************************************/
	class dtModel
	{
	public:
		dtModel();
		virtual ~dtModel();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	private:
		Assimp::Importer m_Importer;			/*!< Assimp importer data object */
		const aiScene* m_Scene;					/*!< Assimp scene object */

	public:
		std::vector<dtMesh*> m_MeshList;		/*!< Mesh array data */
		soMatrix4x4 m_Transform;				/*!< Describe the model transform matrix */
		soMatrix4x4 m_RTransform;				/*!< Describe the model Rtransform matrix */
		uint32 m_TotalVertex;					/*!< Total vertex */
		uint32 m_TotalMesh;						/*!< Total mesh */
		uint32 m_RenderBitKey;					/*!< Render flag */

		/************************************************************************/
		/* Functions									                        */
		/************************************************************************/
	private:
		RESULT ReadFileInfo(soString _FilePath);/*!< Read all the file 3D model info */
		void ShutDown();						/*!< Free all class reources */

	public:
		RESULT StartUp(soString _FilePath);		/*!< Create all the information an prepare to use it */
		void Render(uint32 _ProgramID);			/*!< Render the model with assign shader program */
	};
}
