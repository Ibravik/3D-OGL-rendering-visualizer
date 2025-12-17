/********************************************************************
LC			10/17/2016
Created:	2015/11/10
Filename:	omCorestd.h
Author:		Lehi Muñoz y  Alejandro Rodriguez

Purpose:	Inclucion de Cabeceras standar de C
*********************************************************************/
#pragma once
#pragma warning(disable : 4091)//Esto desabilita el mensaje de outpút relacionado con archivos del sdk w 8.1
#pragma warning(disable : 4005)

/************************************************************************/
/* Archivo de cabecera de windows                                       */
/************************************************************************/
#if PLATFORM == WINDOWS_MATH
#include <windows.h>	/*!< Cabecera Standard de Windows */
#define SO_INTRIN_MATH
#include <intrin.h>
#endif

/************************************************************************************************************************/
/* Características de Debugging de la librería RunTime de C             												*/
/************************************************************************************************************************/
#include <crtdbg.h>

/************************************************************************************************************************/
/* Archivos de Cabeceras de RunTime de C	                               												*/
/************************************************************************************************************************/
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <memory.h>
#include <memory>
#include <tchar.h>
#include <time.h>
#include <Tlhelp32.h>
#include <dbghelp.h>
#include <mmsystem.h>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <exception>
#include <functional>
#include <stdexcept>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <shlobj.h>

/************************************************************************************************************************/
/* Archivos de Cabecera de hilos			                               												*/
/************************************************************************************************************************/
#include <omp.h>

/************************************************************************/
/* Cabeceras linkeadas a la libreria                                    */
/************************************************************************/
#pragma warning(default : 4091)
#pragma warning(default : 4005)
