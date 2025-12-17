#/************************************************************************/
/**
* @LC	  3/31/2016
* @file   soFrustrum.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   9/29/2015
* @brief  Declaration of class Radians, to use radians
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once
#pragma warning(disable : 4201)

/************************************************************************/
/* Inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/

namespace SoulSDK
{
	/************************************************************************/
	/* Forward Class declaration                                            */
	/************************************************************************/
	class soMatrix4x4;
	class soPlane;
	class soVector3D;
	class soSphere;
	class soAABB;

	/************************************************************************/
	/* Enumerador de descripcion para los planos del frustum                */
	/************************************************************************/
	enum eFrustumPlanes
	{
		FP_Top = 0,
		FP_Bottom,
		FP_Left,
		FP_Right,
		FP_Far,
		FP_Near,
		FP_TotalPlanes
	};

	/************************************************************************/
	/* Definicion de la clase soFrustrum                                    */
	/************************************************************************/
	class soFrustrum
	{
		/************************************************************************/
		/* Definicion de construcctores y destructor                            */
		/************************************************************************/
	public:
		soFrustrum();														/*!< Constructor Default */
		~soFrustrum();														/*!< Destructor de la clase */

		/************************************************************************/
		/* Variables miembro de la clase                                        */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				soPlane Near;
				soPlane Far;
				soPlane Left;
				soPlane Right;
				soPlane Top;
				soPlane Bottom;
			};
			soPlane m_FrustumPlanes[6];											/*!< Planos de construccion del frustrum*/
		};
				
		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		void ConstructFrustum(soMatrix4x4& _Projection, soMatrix4x4& _View);/*!< Construccion del frustrum (cada vez que ocurra un cambio en la camara) */
		bool IsPointIn(const soVector3D& _Point);							/*!< Punto dentro del frustrum */
		bool IsSphereIn(const soSphere& _Sphere);							/*!< Esfera dentro de frustrum */
		bool IsAABBIn(const soAABB& _AABB);									/*!< Caja AABB dentro */
	};
}
#pragma warning(default : 4201)