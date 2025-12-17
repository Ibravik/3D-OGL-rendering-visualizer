/************************************************************************/
/**
* @LC	  3/31/2016
* @file   soColor.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   10/17/2015
* @brief  Declaration of class Color
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once
#pragma warning(disable : 4201)

/************************************************************************/
/* inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/

namespace SoulSDK
{
	/************************************************************************/
	/* Definicion de la clase soColor                                       */
	/************************************************************************/
	class soColorRGBA
	{
		/************************************************************************/
		/* Esctructura contenedora de las variables de color                    */
		/************************************************************************/
	public:
		union																				/*!< Estructura que almacena la informacion de un pixel */
		{
			struct
			{
				unsigned char r, g, b, a;													/*!< Canales de cada color & alfa 0x00*/
			};
			unsigned int l;																	/*!< Variable que contiene a los colores 0x000000FF*/
		};
					
		/************************************************************************/
		/* Definicion de construcctores y destructor                            */
		/************************************************************************/
	public:
		explicit soColorRGBA(const unsigned int& _l = 0xAAAAAAFF) : l(_l) {};				/*!< Constructor que pide un valor PIXEL predeterminado */
		soColorRGBA(const unsigned char _RGBA[4]);											/*!< Constructor que pide un valor PIXEL predeterminado */
		soColorRGBA(const short& _r, const short& _g, const short& _b , const short& _a );	/*!< Constructor que pide los valores de color del pixel predeterminado */
		soColorRGBA(const soColorRGBA& _CopyObj);											/*!< Constructor que crea un objeto copia del objeto recibido*/

		~soColorRGBA();																		/*!< Destructor de la clase */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		void operator=	(const unsigned int& _Value);										/*!< Iguala un long a soColorRGBA */
		unsigned char& operator[]		(const unsigned int& _Index);						/*!< Retorna el color segun el indice especificado, maximo 4 (0,1,2,3) */
		soColorRGBA operator+	(const soColorRGBA& _Color);								/*!< Suma 2 objetos soColorRGBA */
		soColorRGBA operator-	(const soColorRGBA& _Color);								/*!< Resta 2 objetos soColorRGBA */
		void operator+=	(const soColorRGBA& _Color);										/*!< Suma 2 objetos soColorRGBA */
		void operator-=	(const soColorRGBA& _Color);										/*!< Resta 2 objetos soColorRGBA */
		bool operator== (const soColorRGBA& _Color);										/*!< Comparacion positiva entre 2 objetos soColorRGBA */
		bool operator!= (const soColorRGBA& _Color);										/*!< Comparacion negativa entre 2 objetos soColorRGBA */
	};
}
#pragma warning(default : 4201)