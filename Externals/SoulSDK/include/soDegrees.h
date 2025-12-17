/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soDegrees.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   9/29/2015
* @brief  Declaration of Degrees, for use degrees
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/

namespace SoulSDK
{
	/************************************************************************/
	/* Forward class declaration                                            */
	/************************************************************************/
	class soRadians;

	/************************************************************************/
	/* Definicion de la clase soDegrees	                                    */
	/************************************************************************/
	class soDegrees
	{
		/************************************************************************/
		/* Definicion de construcctores y destructor                            */
		/************************************************************************/
	public:
		explicit soDegrees(const float& _Value = 0.0f) :m_fDegrees(_Value) {};					/*!< Constructor que pide un valor predeterminado */
		soDegrees(const soDegrees& _CopyObj);													/*!< Constructor que crea un objeto copia del objeto recibido*/
		soDegrees(const soRadians& _CopyObj);													/*!< Constructor que crea un objeto copia del objeto recibido*/

		~soDegrees();																			/*!< Destructor de la clase */

		/************************************************************************/
		/* Variables miembro de la clase                                        */
		/************************************************************************/
	public:
		float m_fDegrees;																		/*!< Variable para guardar el valor en grados de un angulo */

		/************************************************************************/
		/* funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		float GetRadians() const;																/*!< Funcion virtual para convercion a radianes */
		float GetDegrees() const;																/*!< Funcion virtual para convercion a grados euclideanos */
		void Unwind();																			/*!< Funcion que retorna el angulo dentro de la circunferencia, si este excede el maximo solo cambia ru representacion */
		bool Equal(const float& _Value, float _Precision) const;								/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(float& _Value, float _Precision) const;										/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(const soDegrees& _Euler, float _Precision) const;							/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(soDegrees& _Euler, float _Precision) const;									/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(const soRadians& _Radian, float _Precision) const;							/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(soRadians& _Radian, float _Precision) const;									/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/

		/************************************************************************/
		/* Sobrecarga de operadores		                                        */
		/************************************************************************/
		void operator=		(const soRadians& _Radians);										/*!< Iguala un objeto omDegree a otro */
		void operator=		(const soDegrees& _Degrees);										/*!< Iguala un objeto omDegree a otro */
		void operator=		(const float& _Value);												/*!< Asigna un valor a la variable m_fDegrees */

		friend soDegrees operator+	(const soDegrees& _Degrees1, const soDegrees& _Degrees2);	/*!< Suma de la variable m_fDegrees entre 2 objetos omDegree */
		friend soDegrees operator+	(soDegrees& _Degrees1, const soDegrees& _Degrees2);			/*!< Suma de la variable m_fDegrees entre 2 objetos omDegree */
		friend soDegrees operator+	(const soDegrees& _Degrees1, soDegrees& _Degrees2);			/*!< Suma de la variable m_fDegrees entre 2 objetos omDegree */
		friend soDegrees operator+	(soDegrees& _Degrees1, soDegrees& _Degrees2);				/*!< Suma de la variable m_fDegrees entre 2 objetos omDegree */
		soDegrees operator+	(const soRadians& _Radians);										/*!< Suma de la variable m_fDegrees, el valor tomado de soRadians se convierte a grados euler */
		soDegrees operator+	(soRadians& _Radians);												/*!< Suma de la variable m_fDegrees, el valor tomado de soRadians se convierte a grados euler */
		friend soDegrees operator+	(const soDegrees& _Degrees, const float& _Value);			/*!< Suma de la variable m_fDegrees y un valor flotante */
		friend soDegrees operator+	(const float& _Value, const soDegrees& _Degrees);			/*!< Suma de la variable m_fDegrees y un valor flotante */

		friend soDegrees operator-	(const soDegrees& _Degrees1, const soDegrees& _Degrees2);	/*!< Resta de la variable m_fDegrees entre 2 objetos omDegree */
		friend soDegrees operator-	(soDegrees& _Degrees1, const soDegrees& _Degrees2);			/*!< Resta de la variable m_fDegrees entre 2 objetos omDegree */
		friend soDegrees operator-	(const soDegrees& _Degrees1, soDegrees& _Degrees2);			/*!< Resta de la variable m_fDegrees entre 2 objetos omDegree */
		friend soDegrees operator-	(soDegrees& _Degrees1, soDegrees& _Degrees2);				/*!< Resta de la variable m_fDegrees entre 2 objetos omDegree */
		soDegrees operator-	(const soRadians& _Radians);										/*!< Resta de la variable m_fDegrees, el valor tomado de soRadians se convierte a grados euler */
		soDegrees operator-	(soRadians& _Radians);												/*!< Resta de la variable m_fDegrees, el valor tomado de soRadians se convierte a grados euler */
		friend soDegrees operator-	(const soDegrees& _Degrees, const float& _Value);			/*!< Resta de la variable m_fDegrees y un valor flotante */
		friend soDegrees operator-	(const float& _Value, const soDegrees& _Degrees);			/*!< Resta de la variable m_fDegrees y un valor flotante */

		void operator+=	(const soDegrees& _Degrees);											/*!< Suma de la variable m_fDegrees entre 2 objetos omDegree */
		void operator+=	(const soRadians& _Radians);											/*!< Suma de la variable m_fDegrees, el valor tomado de soRadians se convierte a grados euler */
		void operator+=	(const float& _Value);													/*!< Suma de la variable m_fDegrees y un valor flotante */
		friend void operator+=	(float& _Value, soDegrees& _Degrees);							/*!< Suma de la variable m_fDegrees y un valor flotante */

		void operator-=	(const soDegrees& _Degrees);											/*!< Suma de la variable m_fDegrees entre 2 objetos omDegree */
		void operator-=	(const soRadians& _Radians);											/*!< Suma de la variable m_fDegrees, el valor tomado de soRadians se convierte a grados euler */
		void operator-=	(const float& _Value);													/*!< Suma de la variable m_fDegrees y un valor flotante */
		friend void operator-=	(float& _Value, const soDegrees& _Degrees);						/*!< Suma de la variable m_fDegrees y un valor flotante */

		bool operator==	(const soDegrees& _Degrees);											/*!< Comparacion de igualdad entre el valor de m_fDegrees, se convierte el valor de objeto soRadians a grados euler */
		bool operator==	(const soRadians& _Radians);											/*!< Comparacion de igualdad entre el valor de m_fDegrees entre 2 objetos soDegrees */
		bool operator!=	(const soDegrees& _Degrees);											/*!< Comparacion de diferencia entre el valor de m_fDegrees, se convierte el valor de objeto soRadians a grados euler */
		bool operator!=	(const soRadians& _Radians);											/*!< Comparacion de diferencia entre el valor de m_fDegrees entre 2 objetos soDegrees */
	};
}

