/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soMatrix3D.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   10/18/2015
* @brief  Declaration of class soMatrix3D
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
	/* forward class delcaration                                            */
	/************************************************************************/
	class soVector3D;

	/************************************************************************/
	/* Definicion de la clase soMatrix3D                                    */
	/************************************************************************/
	class soMatrix3x3
	{
		/************************************************************************/
		/* Declaracion de estructura matrix			                            */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				float	m00, m01, m02,
						m10, m11, m12,
						m20, m21, m22;
			};
			struct
			{
				float	_11, _12, _13,
						_21, _22, _23,
						_31, _32, _33;
			};
			float Line[3][3];
			float fMatrix[9];
		};

		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:
		soMatrix3x3(const float& _m00 = 0.0f, const float& _m01 = 0.0f, const float& _m02 = 0.0f,
			const float& _m10 = 0.0f, const float& _m11 = 0.0f, const float& _m12 = 0.0f,
			const float& _m20 = 0.0f, const float& _m21 = 0.0f, const float& _m22 = 0.0f) :
			m00(_m00), m01(_m01), m02(_m02),
			m10(_m10), m11(_m11), m12(_m12),
			m20(_m20), m21(_m21), m22(_m22) {};									/*!< m10 Constructor que pide los 9 elementos en orden */
		soMatrix3x3(const float m0[3], const float m1[3], const float m2[3]);	/*!< Constructor que pide 3 arreglos de 3 elementos */
		soMatrix3x3(const soMatrix3x3& _CopyObj);								/*!< Constructor que crea un objeto copia del objeto recibido*/

		~soMatrix3x3();															/*!< Destructor de la clase */

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		void ResetMatrix();														/*!< Inicializa las variables de la matriz a 0 */
		bool Equal(const soMatrix3x3& _Matrix3x3, float _Precision);			/*!< Verifica si las matrices son equivalentes tomando en cuenta el grado de precision de math */
		bool Equal(soMatrix3x3& _Matrix3x3, float _Precision);					/*!< Verifica si las matrices son equivalentes tomando en cuenta el grado de precision de math */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
		void operator=          (soMatrix3x3 _Matrix3x3);						/*!< Igualacion de matrices */
		soMatrix3x3 operator+	(const soMatrix3x3& _Matrix3x3);				/*!< Suma entre 2 matrices */
		soMatrix3x3 operator-	(const soMatrix3x3& _Matrix3x3);				/*!< Resta entre 2 matrices */
		soMatrix3x3 operator*	(const soMatrix3x3& _Matrix3x3);				/*!< Multiplicacion entre 2 matrices */
		soVector3D operator*	(const soVector3D& _Vector3D);					/*!< Multiplicacion entre 2 matrices (3x3 & 3x1) */
		soMatrix3x3 operator*	(const float& _Value);							/*!< Multiplicacion entre 1 matriz y un flotante */

		void operator+=	(const soMatrix3x3& _Matrix3x3);						/*!< Suma entre 2 matrices */
		void operator-=	(const soMatrix3x3& _Matrix3x3);						/*!< Resta entre 2 matrices */
		void operator*=	(const soMatrix3x3& _Matrix3x3);						/*!< Multiplicacion entre 2 matrices */
		void operator*=	(const soVector3D& _Vector3D);							/*!< Multiplicacion entre 2 matrices (3x3 & 3x1) */
		void operator*=	(const float& _Value);									/*!< Multiplicacion entre 1 matriz y un flotante */

		bool operator==			(const soMatrix3x3& _Matrix3x3);				/*!< Comparacion positiva entre 2 matrices */
		bool operator!=			(const soMatrix3x3& _Matrix3x3);				/*!< Comparacion negativa entre 2 matrices */
	};
}
#pragma warning(default : 4201)