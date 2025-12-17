/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soAABB.h
* @Author Aldo Muñoz & Raul Portillo (lehi.munoz@gmail.com)
* @date   10/14/2015
* @brief  Declaration of class AABB(Geometry)
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras necesarias para compilar                      */
/************************************************************************/

namespace SoulSDK
{
	/************************************************************************/
	/* Forward Class Declaration                                            */
	/************************************************************************/
	class soVector3D;

	/************************************************************************/
	/* Declaracion de la clase soAABB	                                    */
	/************************************************************************/
	class soAABB : public soPhysicObject
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		soAABB();																					/*!< Constructor Standar */
		soAABB(const soVector3D& _Center, const soVector3D& _AABBMax, const soVector3D& _AABBMin);	/*!< Constructor que recive objetos predeterminados */
		soAABB(const soAABB& _AABB);																/*!< Constructor Copia */
		~soAABB();																					/*!< Destructor */

		/************************************************************************/	
		/* Declaracion de variables miembro de la clase                         */	
		/************************************************************************/	
	public:
		soVector3D m_AABBCenter;																	/*!< Punto Central del AABB */
		soVector3D m_AABBMax;																		/*!< Puntos Maximos de la caja de colicion */
		soVector3D m_AABBMin;																		/*!< Puntos minimos de la caja de colicion */

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		bool Equal(const soAABB& _AABB, float _Precision)const;										/*!< Verifica si las cajas son equivalentes en su composicion */					
		bool Equal(soAABB& _AABB, float _Precision)const;											/*!< Verifica si las cajas son equivalentes en su composicion */
		virtual bool IsCollition(soPhysicObject* _PhysicObject);									/*!< Verifica coliciones entre el objeto y otro objeto */
		
		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		bool operator ==	(const soAABB& _AABB);													/*!< Comparacion positiva entre 2 cajas de colicion */
		bool operator !=	(const soAABB& _AABB);													/*!< Comparacion negativa entre 2 cajas de colicion */
	};
}