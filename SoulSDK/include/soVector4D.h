/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soVector4D.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   10/17/2015
* @brief  Declaration of class soVector4D
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
	class soDegrees;
	class soRadians;
	class soVector2D;
	class soVector3D;
	class soMatrix4x4;

	/************************************************************************/
	/* Definicion de la clase soVector4D                                    */
	/************************************************************************/
	class soVector4D
	{
		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:
		explicit soVector4D(const float&  _X = 0.0f, const float& _Y = 0.0f, const float& _Z = 0.0f, const float& _W = 0.0f) :X(_X), Y(_Y), Z(_Z), W(_W) {};/*!< Constructor que pide un valor predeterminado */
		soVector4D(const soVector2D& _CopyObj);																												/*!< Constructor que crea un objeto copia del objeto recibido */
		soVector4D(const soVector3D& _CopyObj);																												/*!< Constructor que crea un objeto copia del objeto recibido */
		soVector4D(const soVector4D& _CopyObj);																												/*!< Constructor que crea un objeto copia del objeto recibido */

		~soVector4D();																																		/*!< Destructor de la clase */

																																							/*!< Almacena los valores de los componentes del vector *
		/************************************************************************/
		/* Esctructura contenedora de las variables de vectror                  */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				float X, Y, Z, W;
			};
			struct
			{
				float a, b, c, d;
			};
			struct
			{
				float x, y, z, w;
			};
			float Vector[4];
		};

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		bool Equal(soVector4D _Vector4D, float _Precision)const;																							/*!< Verifica la equivalencia entre 2 vectores con un grado de error de precision*/

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
		void operator=	(const soVector2D& _Vector2D);																										/*!< Iguala los componentes xy de un vector2D en uno 4D */
		void operator=	(const soVector3D& _Vector3D);																										/*!< Iguala los componentes xy< de un vector3D en uno 4D */
		void operator=	(const soVector4D& _Vector4D);																										/*!< Iguala los componentes xy de un vector2D en uno 4D */

		soVector4D operator-	(const soVector4D& _Vector4D);																								/*!< Resta entre el valor por eje */
		soVector4D operator-	();																															/*!< Niega el valor por eje */
		soVector4D operator+	(const soVector4D& _Vector4D);																								/*!< Suma entre el valor por eje */
		soVector4D operator*	(const soVector4D& _Vector4D);																								/*!< Multiplicacion de el valor de cada eje por otro */
		soVector4D operator*	(const soMatrix4x4& _Matrix4x4);																							/*!< Multiplicacion entre un vector y una matriz, resultando en un vector */
		soVector4D operator*	(const float& _Value);																										/*!< Multiplicacion de el valor de cada eje por un floatante */
		soVector4D operator/	(const float& _Value);																										/*!< Divicion de el valor de cada eje por un floatante */

		void operator+=	(const soVector4D& _Vector4D);																										/*!< Suma entre el valor por eje */
		void operator-=	(const soVector4D& _Vector4D);																										/*!< Resta entre el valor por eje */
		void operator*=	(const soVector4D& _Vector4D);																										/*!< Multiplicacion de el valor de cada eje por otro */
		void operator*=	(const soMatrix4x4& _Matrix4x4);																									/*!< Multiplicacion entre un vector y una matriz, resultando en un vector */
		void operator*=	(const float& _Value);																												/*!< Multiplicacion de el valor de cada eje por un floatante */
		void operator/=	(const float& _Value);																												/*!< Multiplicacion de el valor de cada eje por un floatante */

		float& operator[]		(const unsigned int& _Index);																								/*!< Retorna el valor de cada eje segun el indice, maximo 4 (0,1,2,3) */
		bool operator==			(const soVector4D& _Vector4D);																								/*!< Comparacion afirmativa entre el valor por eje */
		bool operator!=			(const soVector4D& _Vector4D);																								/*!< Comparacion negativa entre el valor por eje */
	};
}
#pragma warning(default : 4201)