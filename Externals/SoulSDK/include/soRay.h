/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soRay.h
* @Author Aldo Muñoz & Raul Portillo (lehi.munoz@gmail.com)
* @date   10/14/2015
* @brief  Declaration of class soRay(Geometry)
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras necesarias para compilar                      */
/************************************************************************/
#include "soPhysicObject.h"

namespace SoulSDK
{
	/************************************************************************/
	/* Declaracion de la clase soRay                                        */
	/************************************************************************/
	class soRay : public soPhysicObject
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		soRay();														/*!< Constructor Standard */
		soRay(const soVector3D& _Origin, const soVector3D& _Direction);	/*!< Constructor que recive parametros predeterminados */
		soRay(const soRay& _Ray);										/*!< Constructor Copia */
		virtual ~soRay();												/*!< Destructor */

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	public:
		soVector3D m_VecOrigin;											/*!< Punto donde se origina(inicia) el rayo */
		soVector3D m_VecDirection;										/*!< Direccion del Rayo */
		
		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		bool Equal(const soRay& _Ray, float _Presicion)const;			/*!< Verifica si las cajas son equivalentes en su composicion */
		bool Equal(soRay& _Ray, float _Presicion)const;					/*!< Verifica si las cajas son equivalentes en su composicion */
		virtual bool IsCollition(soPhysicObject* _PhysicObject);		/*!< Verifica coliciones entre el objeto y otro objeto */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		bool operator ==	(const soRay& _Ray);
		bool operator !=	(const soRay& _Ray);
	};
}
