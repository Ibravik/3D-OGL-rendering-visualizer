/********************************************************************/
/**
* @file   soModule.h
* @author Samuel Prince (samuel.prince.quezada@gmail.com)
* @date   2015/02/22
* @brief  Represents one engine module
*
* Represents one engine module. Essentially it is a specialized type
* of singleton. Module must be manually started up and shut down
* before and after use.
*
* @bug	   No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************************************************************/
/* Includes                                                                     										*/
/************************************************************************************************************************/
#include "soPlatformTypes.h"
#include "soMacros.h"

namespace SoulSDK
{
	/************************************************************************************************************************/
	/**
	* @brief	Represents one engine module. Essentially it is a specialized type of singleton. Module must be manually
	*			started up and shut down before and after use.
	*/
	/************************************************************************************************************************/
	template <class T, class ...Args>
	class soModule
	{
	public:
		/************************************************************************************************************************/
		/**
		* @brief	Returns a reference to the module instance. Module has to have been started up first otherwise an exception
		*			will be thrown.
		*/
		/************************************************************************************************************************/
		static T& Instance()
		{
			if (IsShutDown())
			{
				SOE_ThrowException("soModule", "Instance()", "Trying to access a module but it hasn't been started up yet.");
			}

			if (IsDestroyed())
			{
				SOE_ThrowException("soModule", "Instance()", "Trying to access a destroyed module.");
			}

			return *_Instance();
		}

		/************************************************************************************************************************/
		/**
		* @brief	Returns a pointer to the module instance. Module has to have been started up first otherwise an exception
		*			will be thrown.
		*/
		/************************************************************************************************************************/
		static T* InstancePtr()
		{
			if (IsShutDown())
			{
				SOE_ThrowException("soModule", "InstancePtr()", "Trying to access a module but it hasn't been started up yet.");
				return NULL;
			}

			if (IsDestroyed())
			{
				SOE_ThrowException("soModule", "InstancePtr()", "Trying to access a destroyed module.");
				return NULL;
			}

			return _Instance();
		}

		/************************************************************************************************************************/
		/**
		* @brief	Constructs and starts the module using the specified parameters.
		*/
		/************************************************************************************************************************/
		static RESULT StartUp(Args &&...args)
		{
			if (!IsShutDown())
			{
				SOE_ThrowException("soModule", "StartUp()", "Trying to start an already started module.");
				return EC_FALSE;
			}

			_Instance() = SOE_NEW T;
			IsShutDown() = false;

			return _Instance()->__OnStartUp(std::forward<Args>(args)...);
		}

		/************************************************************************************************************************/
		/**
		* @brief	Shuts down this module and frees any resources it is using.
		*/
		/************************************************************************************************************************/
		static void ShutDown()
		{
			if (IsShutDown())
			{
				SOE_ThrowException("soModule", "ShutDown()", "Trying to shut down an already shut down module.");
				return;
			}

			((soModule*)_Instance())->OnShutDown();

			SAFE_DELETE(_Instance());
			IsShutDown() = true;
		}

		/************************************************************************************************************************/
		/**
		* @brief	Query if the module has been started.
		*/
		/************************************************************************************************************************/
		static bool IsStarted()
		{
			return !IsShutDown() && !IsDestroyed();
		}

	protected:
		soModule()
		{
		}

		virtual ~soModule()
		{
			_Instance() = nullptr;
			IsDestroyed() = true;
		}

		soModule(const soModule&)
		{

		}

		soModule& operator=(const soModule&)
		{
			return *this;
		}

	private:
		std::function<RESULT(Args...)>__OnStartUp;			/*!< Puntero a funcion de inicializacion de la clase */

	protected:
		/************************************************************************************************************************/
		/**
		* @brief	Funcion de coneccion entre la funcion standard y la funcion de la clase 
		*
		* @note		Esta funcion es necesaria de llamarse en todas las clases dentro del constructor 
		*/
		/************************************************************************************************************************/
		void Connect(std::function<RESULT(Args...)>func)	/*!< Funcion de coneccion. Se llama dentro del constructor de la clase hija */
		{
			__OnStartUp = func;
		}

		/************************************************************************************************************************/
		/**
		* @brief	Override if you want your module to be notified just before it is deleted.
		*
		* @note		Useful when your module is polymorphic and you might want to perform some kind of clean up perhaps overriding
		*			that of a base class.
		*/
		/************************************************************************************************************************/
		virtual void OnShutDown()
		{

		}

		/************************************************************************************************************************/
		/**
		* @brief	Returns a singleton instance of this module. Throws an exception if module is not yet initialized.
		*/
		/************************************************************************************************************************/
		static T*& _Instance()
		{
			static T* inst = nullptr;
			return inst;
		}

		/************************************************************************************************************************/
		/**
		* @brief	Checks has the Module been shut down.
		*
		* @note		If module was never even started, this will return false.
		*/
		/************************************************************************************************************************/
		static bool& IsDestroyed()
		{
			static bool inst = false;
			return inst;
		}

		/************************************************************************************************************************/
		/**
		* @brief	Checks has the Module been started up.
		*/
		/************************************************************************************************************************/
		static bool& IsShutDown()
		{
			static bool inst = true;
			return inst;
		}
	};
}