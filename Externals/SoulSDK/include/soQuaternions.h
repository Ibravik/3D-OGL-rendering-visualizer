/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soQuaternions.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   2/8/2016
* @brief  Declaration of class soQuaternions
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/

namespace SoulSDK
{
	/************************************************************************/
	/* Forward Class Declaration                                            */
	/************************************************************************/
	class soDegrees;
	class soRadians;
	class soMatrix3x3;

	/************************************************************************/
	/* Enumerador con todas los ordenes de rotacion X, Y, Z                 */
	/************************************************************************/
	enum eOrderAxisRotation
	{
		xyz = 0,
		xzy,
		yxz,
		yzx,
		zxy,
		zyx
	};

	/************************************************************************/
	/* Definicion de la clase soQuaternions                                 */
	/************************************************************************/
	class soQuaternions
	{
		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:
		explicit soQuaternions(const float& _X = 0.0f, const float& _Y = 0.0f, const float& _Z = 0.0f, const float& _W = 1.0f) : X(_X), Y(_Y), Z(_Z), W(_W) {};	/*!< Constructor que pide un valor predeterminado */
		soQuaternions(const soMatrix3x3& _RotationMatrix);																										/*!< Constructor a partir de una matrz de rotacion */
		soQuaternions(const soMatrix4x4& _RotationMatrix);																										/*!< Constructor a partir de una matrz de rotacion */
		soQuaternions(const soVector3D& _Axis, const soDegrees& _EulerAngle);																					/*!< Constructor a partir de un eje y un angulo */
		soQuaternions(const soVector3D& _Axis, const soRadians& _RadianAngle);																					/*!< Constructor a partir de un eje y un angulo en radianes */
		soQuaternions(const soDegrees& _Yaw, const soDegrees& _Pich, const soDegrees& _Roll);																	/*!< Constructor a partir de 3 angulos Euler */
		soQuaternions(const soRadians& _Yaw, const soRadians& _Pich, const soRadians& _Roll);																	/*!< Constructor a partir de 3 angulos Euler */

		~soQuaternions();																																		/*!< Destructor de la clase */

		/************************************************************************/
		/* Esctructura contenedora de las variables del quaternion              */
		/************************************************************************/
	public:
		float X, Y, Z, W;																																		/*!< Almacena los valores de los componentes del quaternion */

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	private:
		void FromMatrixRotation(const soMatrix3x3& _RotationMatrix);																							/*!< Genera un quaternion a partir de una matriz de rotacion */
		void FromMatrixRotation(const soMatrix4x4& _RotationMatrix);																							/*!< Genera un quaternion a partir de una matriz de rotacion */
		void FromAxisAngle(const soVector3D& _Axis, const soDegrees& _EulerAngle);																				/*!< Genera un quaternion a partir de un eje y un angulo de rotaion */
		void FromEulerAngle(const soDegrees& _Yaw, const soDegrees& _Pich, const soDegrees& _Roll);																/*!< Genera un quaternion a partir de 3 angulos euler */
	public:
		bool Equal(const soQuaternions& _Quaternion, float _Precision)const;																					/*!< Verifica si el cuaternion es equivalente a otro con un nivel menor de precision (WARNING) */
		bool Equal(soQuaternions& _Quaternion, float _Precision)const;																							/*!< Verifica si el cuaternion es equivalente a otro con un nivel menor de precision (WARNING) */
	
		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		void operator=		     (soQuaternions _Quaternion);																									/*!< Igualacion binaria */
		soQuaternions operator + (const soQuaternions &_Quaternion);																							/*!< Suma entre cuaterniones */
		soQuaternions operator - (const soQuaternions &_Quaternion);																							/*!< Resta entre Quaterniones */
		soQuaternions operator * (const soQuaternions &_Quaternion);																							/*!< Multiplicacion entre quaterniones */
		soQuaternions operator * (const float& _Value);																											/*!< Multiplicacion por un factor */
		friend soQuaternions operator * (const float& _Value, const soQuaternions &_Quaternion1);																/*!< Multiplicacion por un factor */
		float& operator[]		(const unsigned int& _Index);																									/*!< Retorna el valor de cada eje segun el indice, maximo 4 (0,1,2,3) */

		void operator += (const soQuaternions &q);																												/*!< Suma entre cuaterniones */
		void operator -= (const soQuaternions &q);																												/*!< Resta entre Quaterniones */
		void operator *= (const soQuaternions &q);																												/*!< Multiplicacion entre quaterniones */
		void operator *= (float _Value);																														/*!< Multiplicacion por un factor */
		bool operator==			(const soQuaternions& _Quaternion);																								/*!< Comparacion afirmativa entre el valor por eje */
		bool operator!=			(const soQuaternions& _Quaternion);																								/*!< Comparacion negativa entre el valor por eje */
	};
}