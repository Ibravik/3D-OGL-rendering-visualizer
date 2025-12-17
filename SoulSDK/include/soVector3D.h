/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soVector3D.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   10/17/2015
* @brief  Declaration of class soVector3D
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
	/* Forward Class Declaration                                            */
	/************************************************************************/
	class soVector2D;
	class soVector4D;
	class soMatrix3x3;

	/************************************************************************/
	/* Definicion de la clase soVector3D                                    */
	/************************************************************************/
	class soVector3D
	{
		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:
		explicit soVector3D(const float&  _X = 0.0f, const float& _Y = 0.0f, const float& _Z = 0.0f) :X(_X), Y(_Y), Z(_Z){};	/*!< Constructor que pide un valor predeterminado */
		soVector3D(const soVector2D& _CopyObj);																					/*!< Constructor que crea un objeto copia del objeto recibido */
		soVector3D(const soVector3D& _CopyObj);																					/*!< Constructor que crea un objeto copia del objeto recibido */
		soVector3D(const soVector4D& _CopyObj);																					/*!< Constructor que crea un objeto copia del objeto recibido */

		~soVector3D();																											/*!< Destructor de la clase */

		/************************************************************************/
		/* Esctructura contenedora de las variables de vectror                  */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				float X, Y, Z;
			};
			struct
			{
				float a, b, c;
			};
			struct
			{
				float x, y, z;
			};
			float Vector[3];
		};																														/*!< Almacena los valores de los componentes del vector */

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		bool Equal(soVector3D _Vector3D, float _Precision)const;																/*!< Verifica la equivalencia entre 2 vectores con un grado de error de precision*/

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
		void operator=	(const soVector2D& _Vector2D);																			/*!< Iguala los componentes xy de un vector2D en uno 3D */
		void operator=	(const soVector3D& _Vector3D);																			/*!< Iguala los componentes xy de un vector2D en uno 3D */
		void operator=	(const soVector4D& _Vector4D);																			/*!< Iguala los componentes xyz de un vector4D en uno 3D */

		soVector3D operator-	(const soVector3D& _Vector3D);																	/*!< Resta entre el valor por eje */
		soVector3D operator-	();																								/*!< Niega el valor por eje */
		soVector3D operator+	(const soVector3D& _Vector3D);																	/*!< Suma entre el valor por eje */
		soVector3D operator*	(const soVector3D& _Vector3D);																	/*!< Multiplicacion de el valor de cada eje por un vector */
		soVector3D operator/	(const float& _Value);																			/*!< Divide entre el valor por eje */
		soVector3D operator*	(const float& _Value);																			/*!< Multiplicacion de el valor de cada eje por un floatante */
		soVector3D operator*	(const soMatrix3x3& _Matrix3x3);																/*!< Multiplicacion entre un vector y una matriz, resultando en un vector */

		void operator+=	(const soVector3D& _Vector3D);																			/*!< Suma entre el valor por eje */
		void operator-=	(const soVector3D& _Vector3D);																			/*!< Resta entre el valor por eje */
		void operator/=	(const float& _Value);																					/*!< Divide entre el valor por eje */
		void operator*=	(const float& _Value);																					/*!< Multiplicacion de el valor de cada eje por un floatante */
		void operator*=	(const soMatrix3x3& _Matrix3x3);																		/*!< Multiplicacion entre un vector y una matriz, resultando en un vector */

		bool operator>			(const soVector3D& _Vector3D);																	/*!< Comparacion entre el valor por eje */
		bool operator<			(const soVector3D& _Vector3D);																	/*!< Comparacion entre el valor por eje */
		bool operator==			(const soVector3D& _Vector3D);																	/*!< Comparacion afirmativa entre el valor por eje */
		bool operator!=			(const soVector3D& _Vector3D);																	/*!< Comparacion negativa entre el valor por eje */
		float& operator[]		(const unsigned int& _Index);																	/*!< Retorna el valor de cada eje segun el indice, maximo 3 (0,1,2) */
	};																									
}
#pragma warning(default : 4201)