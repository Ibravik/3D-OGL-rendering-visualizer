/************************************************************************/
/**
* @LC	  4/7/2017
* @file   dtVertexBuffer.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  Declaration of dtVertexBuffer. Manage all the information about
		  a vertex array of a mesh.
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header files inclution                                               */
/************************************************************************/
#include <assimp/scene.h>
#include <Soul_Math.h>

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* Vertex Struct                                                        */
	/************************************************************************/
	struct Vertex
	{
		soVector3D Position;												/*!< Vertex position */
		soVector2D TexCoord;												/*!< Vertex TexCoord */
		soVector3D Normal;													/*!< Vertex normal */
		soVector3D Binormal;												/*!< Vertex normal */
		soVector3D Tangent;													/*!< Vertex normal */		
	};

	/************************************************************************/
	/* dtVertexBuffer class declaration			                            */
	/************************************************************************/
	class dtVertexBuffer
	{
	public:
		dtVertexBuffer();
		~dtVertexBuffer();

		/************************************************************************/
		/* Variables									                        */
		/************************************************************************/
	private:
		std::vector<Vertex> m_VertexList;										/*!< Vertex array data */

	public:
		uint32 m_GLHandleID;													/*!< gl Buffer id */
		uint32 m_VertexCount;													/*!< Vertex count */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		RESULT CreateMeshVertexInfo(const std::vector<aiMesh*>& _MaterialMesh);	/*!< Fill all vertex info */
		RESULT CreateVertexBuffer();											/*!< Bind and assign vertex info */
		void ShutDown();														/*!< Class destroy */

	public:
		RESULT StartUp(const std::vector<aiMesh*>& _MaterialMesh);				/*!< Class init */
	};
}