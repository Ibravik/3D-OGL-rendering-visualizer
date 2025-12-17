/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soPlane.h
* @Author Aldo Muñoz & Raul Portillo (lehi.munoz@gmail.com)
* @date   10/14/2015
* @brief  Declaration of class Plane(Geometry)
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once
#pragma warning(disable : 4201)

/************************************************************************/
/* Inclucion de cabeceras necesarias para compilar                      */
/************************************************************************/
#include "soPhysicObject.h"

namespace SoulSDK
{
	/************************************************************************/
	/* Declaracion de la clase soPlane                                      */
	/************************************************************************/
	class soPlane : public soPhysicObject
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		soPlane();													/*!< Constructor Standard */
		soPlane(const soVector3D& _Normal, const float& _Wvalue);	/*!< Constructor que resive parametros predeterminados */
		soPlane(const soPlane& _Plane);								/*!< Constructor Copia */
		virtual ~soPlane();											/*!< Destructor */

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				soVector3D m_Normal;								/*!< Variable que contiene el vector normal del plano */
				float m_W;											/*!< Origen al plano */
			};
			struct
			{
				float a, b, c, d;
			};
			soVector4D m_V4D;					
		};													

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		bool Equal(const soPlane& _Plane, float _Presicion)const;	/*!< Verifica si las cajas son equivalentes en su composicion */
		bool Equal(soPlane& _Plane, float _Presicion)const;			/*!< Verifica si las cajas son equivalentes en su composicion */
		virtual bool IsCollition(soPhysicObject* _PhysicObject);	/*!< Verifica coliciones entre el objeto y otro objeto */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		bool operator==		(const soPlane& _Plane);				/*!< Comparacion positiva entre planos */
		bool operator!=		(const soPlane& _Plane);				/*!< Comparacion negativa entre planos */
	};
}
#pragma warning(default : 4201)