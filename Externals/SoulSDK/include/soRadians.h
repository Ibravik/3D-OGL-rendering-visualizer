/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soRadians.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   9/29/2015
* @brief  Declaration of class Radians, to use radians
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
	/* Forward class declaration                                            */
	/************************************************************************/
	class soDegrees;

	/************************************************************************/
	/* Definicion de la clase soRadians                                     */
	/************************************************************************/
	class soRadians
	{
		/************************************************************************/
		/* Definicion de construcctores y destructor                            */
		/************************************************************************/
	public:
		explicit soRadians(const float&  _Value = 0.0f) :m_fRadians(_Value) {};					/*!< Constructor que pide un valor predeterminado */
		soRadians(const soRadians& _CopyObj);													/*!< Constructor que crea un objeto copia del objeto recibido*/
		soRadians(const soDegrees& _CopyObj);													/*!< Constructor que crea un objeto copia del objeto recibido*/

		~soRadians();																			/*!< Destructor de la clase */

		/************************************************************************/
		/* Variables miembro de la clase                                        */
		/************************************************************************/
	public:
		float m_fRadians;																		/*!< Guarda el valor del angulo en radianes (en una circunferencia el valor en radianes va de 0 a 2PI) */

		/************************************************************************/
		/* funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		float GetRadians() const;																/*!< Funcion para convercion a radianes */
		float GetDegrees() const;																/*!< Funcion para convercion a grados euclideanos */
		void Unwind();																			/*!< funcion que retorna un angulo dentro de los limites de una circunferencia */
		bool Equal(const float& _Value, float _Precision) const;								/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(float& _Value, float _Precision) const;										/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(const soDegrees& _Euler, float _Precision) const;							/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(soDegrees& _Euler, float _Precision) const;									/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(const soRadians& _Radian, float _Precision) const;							/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/
		bool Equal(soRadians& _Radian, float _Precision) const;									/*!< Verifica si existe una igualdad tomando en cuenta el grado de precision de PlatformMath*/

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
		void operator=		(const soDegrees& _Degrees);										/*!< Iguala un objeto soRadian a un soDegree a otro */
		void operator=		(const soRadians& _Radians);										/*!< Iguala un objeto soRadian a un soDegree a otro */
		void operator=		(const float& _Value);												/*!< Asigna un valor a la variable m_fRadians */

		friend soRadians operator+	(const soRadians& _Radians1, const soRadians& _Radians2);	/*!< Suma de la variable m_fRadians entre 2 objetos soRadian */
		friend soRadians operator+	(soRadians& _Radians1, const soRadians& _Radians2);			/*!< Suma de la variable m_fRadians entre 2 objetos soRadian */
		friend soRadians operator+	(const soRadians& _Radians1, soRadians& _Radians2);			/*!< Suma de la variable m_fRadians entre 2 objetos soRadian */
		friend soRadians operator+	(soRadians& _Radians1, soRadians& _Radians2);				/*!< Suma de la variable m_fRadians entre 2 objetos soRadian */
		soRadians operator+	(const soDegrees& _Degrees);										/*!< Suma de la variable m_fRadians, el valor tomado de soDegree se convierte a radianes */
		soRadians operator+	(soDegrees& _Degrees);												/*!< Suma de la variable m_fRadians, el valor tomado de soDegree se convierte a radianes */
		friend soRadians operator+	(const soRadians& _Radians, const float& _Value);			/*!< Suma de la variable m_fRadians y un valor flotante */
		friend soRadians operator+	(const float& _Value, const soRadians& _Radians);			/*!< Suma de la variable m_fRadians y un valor flotante */

		friend soRadians operator-	(const soRadians& _Radians1, const soRadians& _Radians2);	/*!< Resta de la variable m_fRadians entre 2 objetos soRadian */
		friend soRadians operator-	(soRadians& _Radians1, const soRadians& _Radians2);			/*!< Resta de la variable m_fRadians entre 2 objetos soRadian */
		friend soRadians operator-	(const soRadians& _Radians1, soRadians& _Radians2);			/*!< Resta de la variable m_fRadians entre 2 objetos soRadian */
		friend soRadians operator-	(soRadians& _Radians1, soRadians& _Radians2);				/*!< Resta de la variable m_fRadians entre 2 objetos soRadian */
		soRadians operator-	(const soDegrees& _Degrees);										/*!< Resta de la variable m_fRadians, el valor tomado de soDegree se convierte a radianes */
		soRadians operator-	(soDegrees& _Degrees);												/*!< Resta de la variable m_fRadians, el valor tomado de soDegree se convierte a radianes */
		friend soRadians operator-	(const soRadians& _Radians, const float& _Value);			/*!< Resta de la variable m_fRadians y un valor flotante */
		friend soRadians operator-	(const float& _Value, const soRadians& _Radians);			/*!< Resta de la variable m_fRadians y un valor flotante */

		void operator+=	(const soDegrees& _Degrees);											/*!< Suma de la variable m_fRadians entre 2 objetos omDegree */
		void operator+=	(const soRadians& _Radians);											/*!< Suma de la variable m_fRadians, el valor tomado de soRadians se convierte a grados euler */
		void operator+=	(const float& _Value);													/*!< Suma de la variable m_fRadians y un valor flotante */
		friend void operator+=	(float& _Value, soRadians& _Degrees);							/*!< Suma de la variable m_fRadians y un valor flotante */

		void operator-=	(const soDegrees& _Degrees);											/*!< Suma de la variable m_fRadians entre 2 objetos soRadian */
		void operator-=	(const soRadians& _Radians);											/*!< Suma de la variable m_fRadians, el valor tomado de soRadians se convierte a radianes */
		void operator-=	(const float& _Value);													/*!< Suma de la variable m_fRadians y un valor flotante */
		friend void operator-=	(float& _Value, const soRadians& _Radians);						/*!< Suma de la variable m_fRadians y un valor flotante */

		bool operator==	(const soRadians& _Radians);											/*!< Comparacion de igualdad entre el valor de m_fRadians, se convierte el valor de objeto soRadians a grados euler */
		bool operator==	(const soDegrees& _Degrees);											/*!< Comparacion de igualdad entre el valor de m_fRadians entre 2 objetos soRadian */
		bool operator!=	(const soRadians& _Radians);											/*!< Comparacion de diferencia entre el valor de m_fRadians, se convierte el valor de objeto soDegree a grados euler */
		bool operator!=	(const soDegrees& _Degrees);											/*!< Comparacion de diferencia entre el valor de m_fRadians entre 2 objetos soRadian */
	};
}
