/************************************************************************/
/**
* @LC	  30/05/2016
* @file   soPoint.h
* @Author Aldo Muñoz(lehi.munoz@gmail.com)
* @date   30/05/2016
* @brief  Declaration of class soPoint(Geometry)
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras necesarias para compilar                      */
/************************************************************************/
#include "Soul_StandardTools.h"

namespace SoulSDK
{
	/************************************************************************/
	/* Forward Class Declaration                                            */
	/************************************************************************/

	/************************************************************************/
	/* Declaracion de la clase soPoint	                                    */
	/************************************************************************/
	class soPoint
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		explicit soPoint(const int32& _X = 0, const int32& _Y = 0) :
			X(_X), Y(_Y) {};						/*!< Constructor que recive objetos predeterminados */
		soPoint(const soPoint& _Point);				/*!< Constructor Copia */
		~soPoint();									/*!< Destructor */

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	public:
		int32 X;									/*!< Posicion X del Rect en espacio de pantalla */
		int32 Y;									/*!< Posicion Y del Rect en espacio de pantalla */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		bool operator ==	(const soPoint& _Point);/*!< Comparacion positiva entre 2 cajas de colicion */
		bool operator !=	(const soPoint& _Point);/*!< Comparacion negativa entre 2 cajas de colicion */
	};
}
