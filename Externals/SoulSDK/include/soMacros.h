/************************************************************************/
/**
* @LC	  10/21/2016
* @file   soMacros.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com) y alejandro Rodriguez (alejandro.rodriguez92@gmail.com)
* @date   9/29/2014
* @brief  Declaration of usefull soMacros
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/
#include "soStandardTools.h"
#include "soPlatformTypes.h"

/************************************************************************/
/* crea de manera automatica una variable miembro de una clase con su	*/
/* respectivo Set & Get													*/
/************************************************************************/
/*!< Macro Definition: Crea una variable con accesor de seguridad de lectura Get  y acceso de escritura SET */
#define SET_AND_GET(Type, a)																		\
	public:																							\
	INLINE Type& Get##a##(){return m_##a##;}														\
	INLINE void Set##a##(Type& B){m_##a## = B;}														\
	protected:																						\
	Type m_##a##;																					\
	public:

/*!< Macro Definition: Crea una variable con accesor de seguridad de lectura Get */
#define GET_SAFE(Type, a)																			\
	public:																							\
	INLINE Type Get##a##(){return m_##a##;}															\
	protected:																						\
	Type m_##a##;																					\
	public:

/************************************************************************/
/* soMacros para alojamiento de memoria en versiones DEBUG y RELEASE    */
/************************************************************************/
#if defined(_DEBUG)
#	define SOE_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define SOE_NEW new
#endif

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(x){ if(x != NULL) delete x; x=NULL;}
#endif

#if !defined(SAFE_FREE)
#define SAFE_FREE(x) if(x != NULL) free(x); x=NULL;
#endif

#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(x) if (x != NULL) delete[] x; x=NULL; 
#endif

#if !defined(SAFE_RELEASE)
#define SAFE_RELEASE(x) if(x != NULL) x->Release(); x=NULL;
#endif

#if !defined(SAFE_DELETE_STDVECTOR)
#define SAFE_DELETE_STDVECTOR(x) while(!x.empty()){ SAFE_DELETE(x.back()); x.back() = NULL; x.pop_back();};
#endif


/************************************************************************/
/* Declaracion de macros para reporte de errores                        */
/************************************************************************/
#if defined(_DEBUG)
#define SOE_OutputLOG(_ClassName, _FunctionName, _OutputMessage)		\
OutputDebugStringA(_ClassName);											\
OutputDebugStringA(" : In Function : ");								\
OutputDebugStringA(_FunctionName);										\
OutputDebugStringA(" : ");												\
OutputDebugStringA(_OutputMessage);										\
OutputDebugStringA("\n");

#define SOE_ThrowException(_ClassName, _FunctionName, _OutputMessage)	\
SOE_OutputLOG(_ClassName, _FunctionName, _OutputMessage);				\
throw std::exception();
#else
#define SOE_OutputLOG(_ClassName, _FunctionName, _OutputMessage);
#define SOE_ThrowException(_ClassName, _FunctionName, _OutputMessage);
#endif

/************************************************************************/
/* Macros para manejo de errores                                        */
/************************************************************************/
#pragma warning(disable : 4702)
typedef int32 RESULT;
#define EC_OK               0;
#define EC_FALSE			-1;
#define TOHIT(ErrorCode)(((RESULT)(ErrorCode)) >= 0)
#define FAIL(ErrorCode)	(((RESULT)(ErrorCode)) < 0)

/************************************************************************/
/* soMacros de tipos de función                    					    */
/************************************************************************/
#ifndef VARARGS
#define VARARGS			__cdecl					//Funciones con argumentos variables
#endif
#ifndef CDECL
#define CDECL			__cdecl					//Funciones en Standard C
#endif
#ifndef STDCALL
#define STDCALL			__stdcall				//Convención de llamada Standard
#endif
#ifndef FORCEINLINE
#define FORCEINLINE		__forceinline			//Forza a que el código esté inline
#endif
#ifndef INLINE
#define INLINE			__inline				//sugiere que el codigo este inline
#endif
#ifndef FRIEND
#define FRIEND			friend					//
#endif
#ifndef FORCENOINLINE
#define FORCENOINLINE	__declspec(noinline)	//Forza a que el código NO esté inline
#endif
#ifndef RESTRICT
#define RESTRICT		__restrict				//Restrict indica al compilador que un simbolo no tiene alias en el ambito actual
#endif
#ifndef SUPER
#define SUPER		    __super					//Super indica al compilador que se llamara la funcion de la clase padre
#endif
