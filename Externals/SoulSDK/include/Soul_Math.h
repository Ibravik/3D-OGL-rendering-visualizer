/************************************************************************/
/**
* @LC	  7/09/2016
* @file   Soul_Math.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com) Alejandro Rodriguez (alejandro.rodriguez.navarro92@gmail.com)
* @date   9/22/2015
* @brief  Declaration Math Header
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de cabeceras que incluye la libreria Omicron Math          */
/************************************************************************/
#include "Soul_StandardTools.h"
#include "soPlatformMath.h"				/*!< Funciones matematicas basicas */

#if PLATFORM == WINDOWS_MATH
#include "soWindowsMath.h"				/*!< Funciones matematicas basicas optimisadas para Windows */
#elif PLATFORM == VITA_PLATFORM
#include "soVitaMath.h"					/*!< Funciones matematicas basicas optimizadas para Vita */
#endif

#include "soDegrees.h"					/*!< Manejo de grados euler */
#include "soRadians.h"					/*!< Manejo de radianes */
#include "soRotator.h"					/*!< Manejo de angulos de rotacion*/
#include "soColor.h"					/*!< Manejo de colores en RGBA de 8 bits*/
#include "soVector2D.h"					/*!< Manejo de Vectores en 2D */
#include "soVector3D.h"					/*!< Manejo de Vectores en 3D */
#include "soVector4D.h"					/*!< Manejo de Vectores en 4D */
#include "soQuaternion.h"				/*!< Manejo de quaterniones */
#include "soMatrix3D.h"					/*!< Manejo de Matrices en 3D */
#include "soMatrix4D.h"					/*!< Manejo de Matrices en 4D */
#include "soPoint.h"					/*!< Manejo de puntos en 2D */
#include "soRect.h"						/*!< Manejo de rectangulo en un plano 2D */
#include "soPlane.h"					/*!< Manejo de primitiva basica de colicion (Plano) */
#include "soSphere.h"					/*!< Manejo de primitiva basica de colicion (Esfera) */
#include "soRay.h"						/*!< Manejo de primitiva basica de colicion (Rayo) */
#include "soAABB.h"						/*!< Manejo de primitiva basica de colicion (Caja) */
#include "soFrustrum.h"					/*!< Manejo de Frustum, necesario para culling Frustum */
#include "soTransform.h"				/*!< Abstraccion de la informacion de transformacion de escalacion, rotacion y traslacion */
#include "soPhysicObject.h"

/************************************************************************/
/* Linkeo de librerias                                                  */
/************************************************************************/
//Linkeo de librerias necesarias
#pragma comment(lib, "SoulStandardTools")