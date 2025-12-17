/************************************************************************/
/**
* @LC	  16/09/2016
* @file   soTransform.h
* @Author Lehi Munoz (lehi.munoz@gmail.com)
* @date   8/09/2016
* @brief  Declaration of base class soTransform. El transform abstrae la
		  informacion de rotacion, escalacion y traslacion de un objeto al
		  que se ligue, dando facilidad de obtener una matriz transformacion
		  que facilite el traslado de la informacion.
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/********************************************************************/
/* Inclusión de cabeceras requeridas                				*/
/********************************************************************/
#include "soRotator.h"
#include "soVector3D.h"
#include "soMatrix4D.h"
#include "Soul_StandardTools.h"

namespace SoulSDK
{
	class soTransform
	{
		/********************************************************************/
		/* Constructores y destructor							    		*/
		/********************************************************************/
	public:
		soTransform();							/*!< Constructor Standard */
		~soTransform();							/*!< Destructor */

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	private:		
		soSphere m_CullingSphere;				/*!< Espefa que representa el actor dentro del mundo, uso exclusivo de culling para scene graph */
		soRotator m_LastRotation;				/*!< Informacion de la rotacion anterior */
		soVector3D m_LastScaling;				/*!< Informacion de la escala anterior */
		soVector3D m_LastPosition;				/*!< Informacion de la Posicion anterior */
		soMatrix4x4 m_LastTransform;			/*!< Matriz con la informacion local de transformacion anterior */
		soMatrix4x4 m_LastParentTransform;		/*!< Matriz con la informacion de la tranformacion del padre, objeto al que se puede empraentar anterior */

	public:
		soRotator m_Rotation;					/*!< Informacion de la rotacion */
		soVector3D m_Scaling;					/*!< Informacion de la escala */
		soVector3D m_Position;					/*!< Informacion de la Posicion */
		soMatrix4x4 m_Transform;				/*!< Matriz con la informacion local de transformacion */
		soMatrix4x4 m_FinalTransform;			/*!< Matriz con la informacion acumulada de la transformacion local y la del padre */
		soMatrix4x4 m_ParentTransform;			/*!< Matriz con la informacion de la tranformacion del padre, objeto al que se puede empraentar */
		
		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	private:
		void SetFinalTransform();				/*!< Actualiza la matriz de transformacion final */

	public:
		soSphere GetCullingSphere();			/*!< Retorna la esfera unitara para culling */
		void Update();							/*!< Actualiza la matriz final en caso de haber cambios */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
		void operator=(soTransform& _Transform);/*!< Igualacion binaria */
	};
}

