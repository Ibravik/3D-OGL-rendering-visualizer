/************************************************************************/
/**
* @LC	  30/05/2016
* @file   soRect.h
* @Author Aldo Muñoz(lehi.munoz@gmail.com)
* @date   30/05/2016
* @brief  Declaration of class Rect(Geometry)
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras necesarias para compilar                      */
/************************************************************************/

namespace SoulSDK
{
	/************************************************************************/
	/* Forward Class Declaration                                            */
	/************************************************************************/
	
	/************************************************************************/
	/* Declaracion de la clase soRect	                                    */
	/************************************************************************/
	class soRect
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		explicit soRect(const int& _X = 0, const int& _Y = 0, const unsigned int& _Width = 0, const unsigned int& _Height = 0) :
			X(_X), Y(_Y), m_Width(_Width), m_Height(_Height) {};							/*!< Constructor que recive objetos predeterminados */
		soRect(const soRect& _Rect);														/*!< Constructor Copia */
		~soRect();																			/*!< Destructor */

	/************************************************************************/
	/* Declaracion de variables miembro de la clase                         */
	/************************************************************************/
	public:
		int X;																				/*!< Posicion X del Rect en espacio de pantalla */
		int Y;																				/*!< Posicion Y del Rect en espacio de pantalla */
		unsigned int m_Width;																/*!< Ancho del rect */
		unsigned int m_Height;																/*!< Alto del rect */

	/************************************************************************/
	/* Sobrecarga de operadores                                             */
	/************************************************************************/
	public:
		bool operator ==	(const soRect& _Rect);											/*!< Comparacion positiva entre 2 cajas de colicion */
		bool operator !=	(const soRect& _Rect);											/*!< Comparacion negativa entre 2 cajas de colicion */
	};
}
