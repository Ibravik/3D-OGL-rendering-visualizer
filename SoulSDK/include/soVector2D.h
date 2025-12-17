/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soVector2D.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   10/17/2015
* @brief  Declaration of class soVector2D
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
	class soVector3D;
	class soVector4D;

	/************************************************************************/
	/* Definicion de la clase soVector2D                                    */
	/************************************************************************/
	class soVector2D
	{
		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:
		explicit soVector2D(const float& _X = 0.0f, const float& _Y = 0.0f) :X(_X), Y(_Y) {};/*!< Constructor que pide un valor predeterminado */
		soVector2D(const soVector2D& _CopyObj);												/*!< Constructor que crea un objeto copia del objeto recibido*/
		soVector2D(const soVector3D& _CopyObj);												/*!< Constructor que crea un objeto copia del objeto recibido*/
		soVector2D(const soVector4D& _CopyObj);												/*!< Constructor que crea un objeto copia del objeto recibido*/

		~soVector2D();																		/*!< Destructor de la clase */

		/************************************************************************/
		/* Esctructura contenedora de las variables de vectror                  */
		/************************************************************************/
	public:
		union
		{
			struct
			{
				float X, Y;
			};
			struct
			{
				float a, b;
			};
			struct
			{
				float x, y;
			};
			float Vector[2];
		};																					/*!< Almacena los valores de los componentes del vector */

		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		bool Equal(soVector2D& _Vector2D, float _Precision)const;							/*!< Verifica la equivalencia entre 2 vectores con un grado de error de precision*/

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		void operator=  (const soVector2D& _Vector2D);										/*!< Igualacion binaria */
		void operator=	(const soVector3D& _Vector3D);										/*!< Iguala los componentes xy de un vector3D en uno 2D */
		void operator=	(const soVector4D& _Vector4D);										/*!< Iguala los componentes xy de un vector4D en uno 2D */

		soVector2D operator+	(const soVector2D& _Vector2D);								/*!< Suma entre el valor por eje */
		soVector2D operator-	(const soVector2D& _Vector2D);								/*!< Resta entre el valor por eje */
		soVector2D operator-	();															/*!< niega el valor por eje */
		soVector2D operator*	(const float& _Value);										/*!< Multiplicacion de el valor de cada eje por un floatante */
		soVector2D operator/	(const float& _Value);										/*!< Divicion de el valor de cada eje por un floatante */

		void operator+=	(const soVector2D& _Vector2D);										/*!< Suma entre el valor por eje */
		void operator-=	(const soVector2D& _Vector2D);										/*!< Resta entre el valor por eje */
		void operator*=	(const float& _Value);												/*!< Multiplicacion de el valor de cada eje por un floatante */
		void operator/=	(const float& _Value);												/*!< Multiplicacion de el valor de cada eje por un floatante */

		bool operator==			(const soVector2D& _Vector2D);								/*!< Comparacion afirmativa entre el valor por eje */
		bool operator!=			(const soVector2D& _Vector2D);								/*!< Comparacion negativa entre el valor por eje */

		float& operator[] (const unsigned int& _Index);										/*!< Retorna el flotante en el lugar correspondiente */
	};
}
#pragma warning(default : 4201)