/************************************************************************/
/**
* @LC	  4/8/2017
* @file   dtMesh.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  Declaration of dtMesh class. It contain all the information for
		  vertex with the same material
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header files include				                                    */
/************************************************************************/
#include <assimp/scene.h>
#include <Soul_Math.h>
#include "dtVertexBuffer.h"
#include "dtIndexBuffer.h"
#include "dtMaterial.h"

namespace DeveloperTest
{
	/************************************************************************/
	/* MeshData struct, contain all the init info for the class             */
	/************************************************************************/
	struct MeshData
	{
		std::vector<aiMesh*> *MeshArray;					/*!< Mesh list with the same material */
		soString FilePath;									/*!< Root file path */
		MaterialData MaterialInitData;						/*!< All the info to init the material of the mesh */

		MeshData()
		{
			MeshArray = nullptr;
		}
	};

	/************************************************************************/
	/* dtMesh class declaration											    */
	/************************************************************************/
	class dtMesh
	{
	public:
		dtMesh();	
		~dtMesh();	

		/************************************************************************/
		/* Variables									                        */
		/************************************************************************/
	public:		
		dtVertexBuffer m_VertexBuffer;				/*!< Vertex Buffer */
		dtIndexBuffer m_IndexBuffer;				/*!< Index Buffer */
		uint32 m_VertexArrayID;						/*!< gl vertex array buffer ID */
		dtMaterial m_Material;						/*!< Mesh material */
		soString m_MeshName;						/*!< Mesh Name */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		void ShutDown();							/*!< Release resources of the class */

	public:
		void Render(uint32 _ProgramID);				/*!< Render assing mesh */
		RESULT StartUp(const MeshData& _MeshInfo);	/*!< Init class */		
	};
}