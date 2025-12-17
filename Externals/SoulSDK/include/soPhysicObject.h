/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soPhysicObject.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   9/8/2016
* @brief  Declaration of class soPhysicObject. Se pretende unicamente 
		  simplificar el uso de objetos fisicos a partir de polimorfismo
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
	/* Forward Class declaration                                            */
	/************************************************************************/

	/************************************************************************/
	/* Declaracion de la clase soSphere                                     */
	/************************************************************************/
	class soPhysicObject
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	public:
		soPhysicObject();											/*!< Constructor Standard */
		virtual ~soPhysicObject();									/*!< Destructor virtual */

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	public:
		
		/************************************************************************/
		/* Funciones de ayuda de la clase                                       */
		/************************************************************************/
	public:
		virtual bool IsCollition(soPhysicObject* _PhysicObject) = 0;	/*!< Verifica coliciones entre el objeto y otro objeto */
	};
}