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
	class soQuaternion
	{
		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:
		explicit soQuaternion(const float& _X = 0.0f, const float& _Y = 0.0f, const float& _Z = 0.0f, const float& _W = 1.0f)
		: X(_X), Y(_Y), Z(_Z), W(_W) {};																						/*!< Constructor que pide un valor predeterminado */
		soQuaternion(const soMatrix3x3& _RotationMatrix);																		/*!< Constructor a partir de una matrz de rotacion */
		soQuaternion(const soMatrix4x4& _RotationMatrix);																		/*!< Constructor a partir de una matrz de rotacion */
		soQuaternion(const soVector3D& _Axis, const soDegrees& _EulerAngle);													/*!< Constructor a partir de un eje y un angulo */
		soQuaternion(const soVector3D& _Axis, const soRadians& _RadianAngle);													/*!< Constructor a partir de un eje y un angulo en radianes */
		soQuaternion(const soDegrees& _Yaw, const soDegrees& _Pich, const soDegrees& _Roll);									/*!< Constructor a partir de 3 angulos Euler */
		soQuaternion(const soRadians& _Yaw, const soRadians& _Pich, const soRadians& _Roll);									/*!< Constructor a partir de 3 angulos Euler */

		~soQuaternion();																										/*!< Destructor de la clase */

		/************************************************************************/
		/* Esctructura contenedora de las variables del quaternion              */
		/************************************************************************/
	public:
		float X, Y, Z, W;																										/*!< Almacena los valores de los componentes del quaternion */

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	private:
		void FromMatrixRotation(const soMatrix3x3& _RotationMatrix);															/*!< Genera un quaternion a partir de una matriz de rotacion */
		void FromMatrixRotation(const soMatrix4x4& _RotationMatrix);															/*!< Genera un quaternion a partir de una matriz de rotacion */
		void FromAxisAngle(const soVector3D& _Axis, const soDegrees& _EulerAngle);												/*!< Genera un quaternion a partir de un eje y un angulo de rotaion */
		void FromEulerAngle(const soDegrees& _Yaw, const soDegrees& _Pich, const soDegrees& _Roll);								/*!< Genera un quaternion a partir de 3 angulos euler */
	public:
		bool Equal(const soQuaternion& _Quaternion, float _Precision)const;														/*!< Verifica si el cuaternion es equivalente a otro con un nivel menor de precision (WARNING) */
		bool Equal(soQuaternion& _Quaternion, float _Precision)const;															/*!< Verifica si el cuaternion es equivalente a otro con un nivel menor de precision (WARNING) */
	
		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		void operator=		     (soQuaternion _Quaternion);																	/*!< Igualacion binaria */
		soQuaternion operator + (const soQuaternion &_Quaternion);																/*!< Suma entre cuaterniones */
		soQuaternion operator - (const soQuaternion &_Quaternion);																/*!< Resta entre Quaterniones */
		soQuaternion operator * (const soQuaternion &_Quaternion);																/*!< Multiplicacion entre quaterniones */
		soQuaternion operator * (const float& _Value);																			/*!< Multiplicacion por un factor */
		friend soQuaternion operator * (const float& _Value, const soQuaternion &_Quaternion1);									/*!< Multiplicacion por un factor */
		float& operator[]		(const unsigned int& _Index);																	/*!< Retorna el valor de cada eje segun el indice, maximo 4 (0,1,2,3) */

		void operator += (const soQuaternion &q);																				/*!< Suma entre cuaterniones */
		void operator -= (const soQuaternion &q);																				/*!< Resta entre Quaterniones */
		void operator *= (const soQuaternion &q);																				/*!< Multiplicacion entre quaterniones */
		void operator *= (float _Value);																						/*!< Multiplicacion por un factor */
		bool operator==			(const soQuaternion& _Quaternion);																/*!< Comparacion afirmativa entre el valor por eje */
		bool operator!=			(const soQuaternion& _Quaternion);																/*!< Comparacion negativa entre el valor por eje */
	};
}