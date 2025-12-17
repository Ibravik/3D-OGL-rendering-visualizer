/************************************************************************/
/**
* @LC	  10/9/2016
* @file   soStandardClass.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   6/29/2016
* @brief  Declaration of soStandardClass. Como intento de standarisar la 
		  creacion de clases y agilizar el desarrollo, la clase 
		  soStandardClass tiene como proposito ser un modulo de inclucion
		  de clases y funciones basicas que todas las clases comparten.
		  Pretende tambien facilitar el manejo de los objetos al deribar de 
		  usa sola clase.
* @bug	  No know Bugs 
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras para compilacion                              */
/************************************************************************/
#include "soMacros.h"
#include "soStandardTools.h"
#include "soPlatformTypes.h"

namespace SoulSDK
{
	/************************************************************************/
	/* Declaracion de la clase soStandardClass							    */
	/************************************************************************/
	template <class ...Args>
	class soStandardClass
	{
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
	protected:
		soStandardClass()									/*!< Constructor Default */
		{
			m_bOn = false;
		}

		virtual ~soStandardClass()							/*!< Destructor */
		{
		}

		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
	private:
		bool m_bOn;											/*!< Bandera de verificacion de inicio */

	private:
		std::function<RESULT(Args...)>__OnStartUp;			/*!< Puntero a funcion de inicializacion de la clase */

		/************************************************************************/
		/* Declaracion de funciones de ayuda de la clase                        */
		/************************************************************************/
	public:
		bool IsStarted()									/*!< Vefirica si la clase esta ya inicializada (true) */
		{
			return m_bOn;
		}

		RESULT StartUp(Args ...args)						/*!< Funcion de inicializacion, esta es la que se llama */
		{
			if (IsStarted())
			{
				SOE_ThrowException("soStandardClass", "StartUp", "Class Already On")
			}

			m_bOn = true;

			return __OnStartUp(std::forward<Args>(args)...);
		}

		void Connect(std::function<RESULT(Args...)>func)	/*!< Funcion de coneccion. Se llama dentro del constructor de la clase hija */
		{
			__OnStartUp = func;
		}

		void ShutDown()										/*!< Libera los recursos solicitados por la clase para su iniciacion */
		{
			m_bOn = false;
			OnShutDown();
		}	

		virtual void OnShutDown() = 0;						/*!< Funcion de finalizacion de la clase */
	};
}
