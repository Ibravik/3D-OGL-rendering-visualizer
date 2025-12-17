/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soSphere.h
* @Author Aldo Muñoz & Raul Portillo (lehi.munoz@gmail.com)
* @date   10/14/2015
* @brief  Declaration of class soSphere(Geometry)
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
	/* Declaracion de la clase soSphere                                     */
	/************************************************************************/
	class soSphere : public soPhysicObject
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		soSphere();													/*!< Constructor Standard */
		soSphere(const soVector3D& _Center, const float& _Radius);	/*!< Constructor que recive valores predeterminados */
		soSphere(const soSphere& _Sphere);							/*!< Constructor Copia */
		virtual ~soSphere();										/*!< Destructor */

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				soVector3D m_SphereCenter;								/*!< Punto del centro de la esfera */
				float m_fRadius;										/*!< Radio de la esfera */
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
		bool Equal(const soSphere& _Sphere, float _Presicion)const;	/*!< Verifica si las cajas son equivalentes en su composicion */
		bool Equal(soSphere& _Sphere, float _Presicion)const;		/*!< Verifica si las cajas son equivalentes en su composicion */
		virtual bool IsCollition(soPhysicObject* _PhysicObject);	/*!< Verifica coliciones entre el objeto y otro objeto */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		void operator =		(soSphere& _Sphere);					/*!< Igualacion binaria */
		bool operator ==	(const soSphere& _Sphere);				/*!< Comparacion positiva entre 2 esferas */
		bool operator !=	(const soSphere& _Sphere);				/*!< Comparacion negativa entre 2 esferas */
	};
}
#pragma warning(default : 4201)