/************************************************************************/
/**
* @LC	  9/8/2016
* @file   soRotator.h
* @Author Alejandro Rodriguez & Aldo Muñoz (alejandro.rodriguez.navarro92@gmail.com / lehi.munoz@gmail.com)
* @date   9/8/2016
* @brief  Declaration of base class soRotator. El rotator abstrae la 
		  informacion de rotacion de un quaternion a grados euler o rad.
		  Dentro del pipeline, Roll Corresponde a Z, yaw a Y y pich a X.
		  Las operaciones de Yaw, Pich Roll son acumulatibas aplicadas al
		  quaternion original.
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/
#include "soQuaternion.h"

namespace SoulSDK
{
	/************************************************************************/
	/* Forward class declaration                                            */
	/************************************************************************/
	class soDegrees;
	class soRadians;
	class soVector4D;
	class soMatrix4x4;

	/************************************************************************/
	/* Definicion de la clase soRotator	                                    */
	/************************************************************************/
	class soRotator
	{
		/************************************************************************/
		/* Definicion de construcctores y destructor                            */
		/************************************************************************/
	public:
		soRotator();																		/*!< Constructor standard */
		soRotator(const float& _Yaw, const float& _Pich, const float& _Roll);				/*!< Constructor a partir de 3 flotantes */
		soRotator(const soDegrees& _Yaw, const soDegrees& _Pich, const soDegrees& _Roll);	/*!< Constructor a partir de 3 grados euler */
		soRotator(const soRadians& _Yaw, const soRadians& _Pich, const soRadians& _Roll);	/*!< Constructor a partir de 3 grados radianes */
		soRotator(const soVector4D& _InfoVector);											/*!< Constructor a partir de la informacion de un vector 4D */
		soRotator(const soQuaternion& _InfoVector);											/*!< Constructor a partir de la informacion de un Quaternion */

		~soRotator();																		/*!< Destructor standard */

		/************************************************************************/
		/* Variables miembro de la clase                                        */
		/************************************************************************/
	private:
		soQuaternion m_Rotation;															/*!< Guarda la informacion de rotacion */

	public:		
		soDegrees m_Pich;
		soDegrees m_Yaw;
		soDegrees m_Roll;

		/************************************************************************/
		/* funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:	
		void GetYaw(soDegrees& _YawOut);													/*!< Retorna en un parametro el Yaw de rotacion */
		void GetYaw(soRadians& _YawOut);													/*!< Retorna en un parametro el Yaw de rotacion */

		void GetPich(soDegrees& _PichOut);													/*!< Retorna en un parametro el Pich de rotacion */
		void GetPich(soRadians& _PichOut);													/*!< Retorna en un parametro el Pich de rotacion */

		void GetRoll(soDegrees& _RollOut);													/*!< Retorna en un parametro el Roll de rotacion */
		void GetRoll(soRadians& _RollOut);													/*!< Retorna en un parametro el Roll de rotacion */

		void GetQuat(soQuaternion& _QuatOut);												/*!< Retorna en un parametro el quaternion */

		void GetYawPichRoll(soDegrees& _YawOut, soDegrees& _PichOut, soDegrees& _RollOut);	/*!< Retorna en parametros de entrada los 3 grados que componen el quaternion */
		void GetYawPichRoll(soRadians& _YawOut, soRadians& _PichOut, soRadians& _RollOut);	/*!< Retorna en parametros de entrada los 3 grados que componen el quaternion */
		void GetRotationMatrix(soMatrix4x4& _RotationMatrix);								/*!< Retorna en un parametro la matriz de rotacion */

		void Yaw(soDegrees& _YawIn);														/*!< Ingresa un parametro el Yaw de rotacion */
		void Yaw(soRadians& _YawIn);														/*!< Ingresa un parametro el Yaw de rotacion */
																							  
		void Pich(soDegrees& _PichIn);														/*!< Ingresa un parametro el Pich de rotacion */
		void Pich(soRadians& _PichIn);														/*!< Ingresa un parametro el Pich de rotacion */
																								  
		void Roll(soDegrees& _RollIn);														/*!< Ingresa un parametro el Roll de rotacion */
		void Roll(soRadians& _RollIn);														/*!< Ingresa un parametro el Roll de rotacion */

		void YawPichRoll(soDegrees& _Yaw, soDegrees& _Pich, soDegrees& _Roll);				/*!< Ingresa parametros de entrada los 3 grados que componen el quaternion */
		void YawPichRoll(soRadians& _Yaw, soRadians& _Pich, soRadians& _Roll);				/*!< Ingresa parametros de entrada los 3 grados que componen el quaternion */
		
		/************************************************************************/
		/* Sobrecarga de operadores		                                        */
		/************************************************************************/
		void operator=		(const soVector4D& _VectorIn);									/*!< Iguala un objeto soVector4D a rotator */
		void operator=		(const soQuaternion& _QuatIn);									/*!< Iguala un objeto soQuaternion a rotator */
		void operator=		(const soRotator& _RotIn);										/*!< Iguala un objeto soQuaternion a rotator */

		bool operator==		(const soQuaternion& _QuatIn);									/*!< Comparacion entre 2 rotators */
		bool operator==		(const soRotator& _RotatorIn);									/*!< Comparacion entre 2 rotaciuones */
		
		bool operator!=		(const soQuaternion& _QuatIn);									/*!< Comparacion entre 2 rotators */
		bool operator!=		(const soRotator& _RotatorIn);									/*!< Comparacion entre 2 rotaciuones */
	};
}

