/************************************************************************/
/**
* @LC	  4/7/2017
* @file   dtIndexBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  Declaration of dtIndexBuffer class. It manage all the index info 
		  array
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header Files inclusion		                                        */
/************************************************************************/
#include <assimp/scene.h>
#include <Soul_Math.h>

namespace DeveloperTest
{
	/************************************************************************/
	/* dtIndexBuffer class declaration		                                */
	/************************************************************************/
	class dtIndexBuffer
	{
	public:
		dtIndexBuffer();
		~dtIndexBuffer();

		/************************************************************************/
		/* Variable										                        */
		/************************************************************************/
	public:
		uint32 m_GLHandleID;													/*!< GL handle ID */
		int32 m_IndexCount;														/*!< Total index count */
		std::vector<uint32> m_IndexList;										/*!< Index array */

		/************************************************************************/
		/* Functions									                        */
		/************************************************************************/
	private:
		RESULT CreateMeshIndexInfo(const std::vector<aiMesh*>& MaterialMesh);	/*!< Create the index info from assimp load scenne */
		void ShutDown();														/*!< Free class resources */
		RESULT CreateIndexBuffer();												/*!< Create the GL buffer object */

	public:
		RESULT StartUp(const std::vector<aiMesh*>& _MaterialMesh);				/*!< Inicializa la clase segun las especificaciones recibidas */
	};
}