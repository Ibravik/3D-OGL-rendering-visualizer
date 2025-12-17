/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soPlatformMath.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   9/22/2015
* @brief  Declaration of non-specific platform math functions
* @bug	  No know Bugs
*/                                                                    
/************************************************************************/
#pragma once

/************************************************************************/
/* Inclucion de archivos necesarios para la compilacion                 */
/************************************************************************/
#include <cmath>
#include <iostream>
#include "soDegrees.h"
#include "soRadians.h"
#include "soVector2D.h"
#include "soVector3D.h"
#include "soVector4D.h"
#include "soMatrix3D.h"
#include "soMatrix4D.h"
#include "soQuaternion.h"
#include "soRect.h"
#include "soPoint.h"
#include "soPlane.h"
#include "soRay.h"
#include "soAABB.h"
#include "soSphere.h"

/************************************************************************/
/* Definicion de constantes para el precompilador		                */
/************************************************************************/
#define MATH_API 

namespace SoulSDK
{
	/************************************************************************/
	/* Enum que define los ejes de pivote para rotacion                     */
	/************************************************************************/
	enum eAxis
	{
		X_Axis = 0,
		Y_Axis,
		Z_Axis,
		W_Axis,
		TOTAL_AXIS
	};

	/************************************************************************/
	/* Estructura de Funciones matematicas sin plataforma especifica        */
	/************************************************************************/
	struct soPlatformMath
	{
		/************************************************************************/
		/* Constantes matematicas comunes                                       */
		/************************************************************************/
		static const float PI;																																					/*!< Constante PI */
		static const float DOUBLE_PI;																																			/*!< Constante 2PI */
		static const float TETRA_PI;																																			/*!< Constante 4PI */
		static const float HALF_PI;																																				/*!< Constante 1/2PI */
		static const float QUARTER_PI;																																			/*!< Constante 1/4PI */
		static const float INVERSE_PI;																																			/*!< Constante 1/PI */
		static const float EULER_NUMBER;																																		/*!< Constante Euler */
		static const float LOG2;																																				/*!< Constante Log2 */
		static const float EPSILON;																																				/*!< Constante Epsilon */
		static const float DEG_TO_RAD;																																			/*!< Constante de convercion de grados euler a radianes */
		static const float RAD_TO_DEG;																																			/*!< Constante de convercion de radianes a grados euler */
		static const float MAX_FLOAT32;																																			/*!< Numero mas grande de punto flotante en x86 */
		static const int MAX_INT32;																																				/*!< Numero mas grande entero con signo en x86 */
		static const float MATH_PRECISION_DEC;																																	/*!< Magic number used for math precision (.1) */
		static const float MATH_PRECISION_CEN;																																	/*!< Magic number used for math precision (.01) */
		static const float MATH_PRECISION_MIL;																																	/*!< Magic number used for math precision (.001) */
		static const float MATH_PRECISION_MIC;																																	/*!< Magic number used for math precision (.0001) */
		static const float MATH_PRECISION_NANO;																																	/*!< Magic number used for math precision (.00001) */
		
		/************************************************************************/
		/* Funciones matematicas Basicas                                        */
		/************************************************************************/
		template<typename T>
		static T MATH_API Sin(T _Value) { return sin(_Value); };																												/*!< Retorna el seno segun el tipo de dato */
		template<>
		static float MATH_API Sin(float _Value) { return sinf(_Value); };																										/*!< Retorna el seno en float, no se garantiza que sean grados euler o radianes especificamente */
		static float MATH_API Sin(const soDegrees& _Angle) { return sinf(_Angle.GetRadians()); };																				/*!< Retorna el seno en Grados Euler */
		static float MATH_API Sin(const soRadians& _Angle) { return sinf(_Angle.GetRadians()); };																				/*!< Retorna el seno en Radianes */

		template<typename T>
		static T MATH_API Cos(T _Value) { return cos(_Value); };																												/*!< Retorna el coseno segun el tipo de dato */
		template<>
		static float MATH_API Cos(float _Value) { return cosf(_Value); };																										/*!< Retorna el coseno en float, no se garantiza que sean grados euler o radianes especificamente */
		static float MATH_API Cos(const soDegrees& _Angle) { return cosf(_Angle.GetRadians()); };																				/*!< Retorna el coseno en Grados Euler */
		static float MATH_API Cos(const soRadians& _Angle) { return cosf(_Angle.GetRadians()); };																				/*!< Retorna el coseno en Radianes */

		template<typename T>
		static T MATH_API Tan(T _Value) { return tan(_Value); };																												/*!< Retorna el tangente segun el tipo de dato */
		template<>
		static float MATH_API Tan(float _Value) { return tanf(_Value); };																										/*!< Retorna el tangente en float, no se garantiza que sean grados euler o radianes especificamente */
		static float MATH_API Tan(const soDegrees& _Angle) { return tanf(_Angle.GetRadians()); };																				/*!< Retorna el tangente en Grados Euler */
		static float MATH_API Tan(const soRadians& _Angle) { return tanf(_Angle.GetRadians()); };																				/*!< Retorna el tangente en Radianes */

		template<typename T>
		static T MATH_API ArcSin(T _Value) { return asin(_Value); };																											/*!< Retorna el arcoseno segun el tipo de dato */
		template<>
		static float MATH_API ArcSin(float _Value) { return asinf(_Value); };																									/*!< Retorna el arcoseno en float, no se garantiza que sean grados euler o radianes especificamente */
		static float MATH_API ArcSin(const soDegrees& _Angle) { return asinf(_Angle.GetRadians()); };																			/*!< Retorna el arcoseno en Grados Euler */
		static float MATH_API ArcSin(const soRadians& _Angle) { return asinf(_Angle.GetRadians()); };																			/*!< Retorna el arcoseno en Radianes */

		template<typename T>
		static T MATH_API ArcCos(T _Value) { return acos(_Value); };																											/*!< Retorna el arcocoseno segun el tipo de dato */
		template<>
		static float MATH_API ArcCos(float _Value) { return acosf(_Value); };																									/*!< Retorna el arcocoseno en float, no se garantiza que sean grados euler o radianes especificamente */
		static float MATH_API ArcCos(const soDegrees& _Angle) { return acosf(_Angle.GetRadians()); };																			/*!< Retorna el arcocoseno en Grados Euler */
		static float MATH_API ArcCos(const soRadians& _Angle) { return acosf(_Angle.GetRadians()); };																			/*!< Retorna el arcocoseno en Radianes */

		template<typename T>
		static T MATH_API ArcTan(T _Value) { return atan(_Value); };																											/*!< Retorna el arcotangente segun el tipo de dato */
		template<>
		static float MATH_API ArcTan(float _Value) { return atanf(_Value); };																									/*!< Retorna el arcotangente en float, no se garantiza que sean grados euler o radianes especificamente */
		static float MATH_API ArcTan(const soDegrees& _Angle) { return atanf(_Angle.GetRadians()); };																			/*!< Retorna el arcotangente en Grados Euler */
		static float MATH_API ArcTan(const soRadians& _Angle) { return atanf(_Angle.GetRadians()); };																			/*!< Retorna el arcotangente en Radianes */

		template<typename T>
		static T MATH_API ArcTan2(T _Value1, T _Value2) { return atan2(_Value1, _Value2); };																					/*!< Retorna el arcotangente segun el tipo de dato */
		template<>
		static float MATH_API ArcTan2(float _Value1, float _Value2) { return atan2f(_Value1, _Value2); };																		/*!< Retorna el arcotangente en float, no se garantiza que sean grados euler o radianes especificamente */

		template<typename T, typename U>
		static T MATH_API LogX(T _Value, U _Base) { return logf(_Value) / logf(_Base); };																						/*!< Retorna el Logaritmo segun el tipo de dato */
		template<>
		static float MATH_API LogX(float _Value, float _Base) { return logf(_Value) / logf(_Base); };																			/*!< Retorna el Logaritmo en float */

		template<typename T>
		static T MATH_API LogN(T _Value) { return logf(_Value) / logf(2.0f); };																									/*!< Retorna el Logaritmo Natural segun el tipo de dato */
		template<>
		static float MATH_API LogN(float _Value) { return logf(_Value) / logf(2.0f); };																							/*!< Retorna el Logaritmo Natural en float */

		template<typename T>
		static T MATH_API LogE(T _Value) { return logf(_Value); };																												/*!< Retorna el Logaritmo base 2 segun el tipo de dato */
		template<>
		static float MATH_API LogE(float _Value) { return logf(_Value); };																										/*!< Retorna el Logaritmo base 2 en float */

		template<typename T>
		static T MATH_API Sqrt(T _Value) { return sqrt(_Value); };																												/*!< Retorna la raiz cuadrada segun el tipo de dato */
		template<>
		static float MATH_API Sqrt(float _Value) { return sqrtf(_Value); };																										/*!< Retorna la raiz cuadrada en float */

		template<typename T>
		static T MATH_API Cbrt(T _Value) { return cbrt(_Value); };																												/*!< Retorna la raiz cubica segun el tipo de dato */
		template<>
		static float MATH_API Cbrt(float _Value) { return cbrtf(_Value); };																										/*!< Retorna la raiz cubica en float */

		template<typename T, typename U>
		static T MATH_API Pow(T _Value, U _Pow) { return pow(_Value, _Pow); };																									/*!< Retorna Potencia segun el tipo de dato */
		template<>
		static float MATH_API Pow(float _Value, int _Pow) { return pow(_Value, _Pow); };																						/*!< Retorna Potencia en float */

		template<typename T>
		static T MATH_API Square(T _Value) { return _Value*_Value; };																											/*!< Retorna la potencia cuadrada segun el tipo de dato */
		template<>
		static float MATH_API Square(float _Value) { return _Value*_Value; };																									/*!< Retorna la potencia cuadrada en float */

		template<typename T>
		static T MATH_API InvSqrt(T _Value) { return 1 / sqrt(_Value); };																										/*!< Retorna la inversa de la raiz cuadrada segun el tipo de dato */
		template<>
		static float MATH_API InvSqrt(float _Value) { return 1 / sqrtf(_Value); };																								/*!< Retorna la inversa de la raiz cuadrada en float */

		template<typename T>
		static T MATH_API Clamp(T _Value, T _MaxValue) { return (_Value <= _MaxValue ? _Value : _MaxValue); };																	/*!< Retorna el valor sin exeder el  maximo establecido */

		template<typename T>
		static T MATH_API Lerp(T& _Start, T& _End, float _Percent) { return (_Start + ((_End - _Start)) * _Percent); };															/*!< Retorna el valor intermedio segun el porsentage transcurrido */

		template<typename T>
		static T MATH_API Min(T _ValueA, T _ValueB) { return (_ValueA <= _ValueB ? _ValueA : _ValueB); };																		/*!< Retorna el minimo entre 2 valores segun el tipo de dato */

		template<typename T>
		static T MATH_API Max(T _ValueA, T _ValueB) { return (_ValueA >= _ValueB ? _ValueA : _ValueB); };																		/*!< Retorna el maximo entre 2 valores segun el tipo de dato */

		template<typename T>
		static T MATH_API Min3(T _ValueA, T _ValueB, T _ValueC) { return Min(Min(_ValueA, _ValueB), _ValueC); };																/*!< Retorna el minimo entre 3 valores segun el tipo de dato */

		template<typename T>
		static T MATH_API Max3(T _ValueA, T _ValueB, T _ValueC) { return Max(Max(_ValueA, _ValueB), _ValueC); };																/*!< Retorna el maximo entre 3 valores segun el tipo de dato */

		template<typename T>
		static void MATH_API Swap(T& _ValueA, T& _ValueB) { T C = _ValueA; _ValueA = _ValueB; _ValueB = C; };																	/*!< Intercambio el valor de las variables segun el tipo de dato (puede haber perdida de informacion entre tipos de datos distintos) */

		template<typename T>
		static T MATH_API Abs(T& _ValueA) { return std::abs(_ValueA); };																										/*!< Return te absolute value */

		/************************************************************************/
		/* Funciones trigonometricas basicas Rapidas                            */
		/************************************************************************/
		__inline static float MATH_API FastSin0(float _Value)																														/*!< Funcion Rapida: Retorna el seno en float, no se garantiza que sea en grados euler o radianes */
		{
			return sinf(_Value);
		}

		__inline static float MATH_API FastSin1(float _Value)																														/*!< Funcion Rapida: Retorna el seno con mas precision en float, no se garantiza que sea en grados euler o radianes */
		{
			return sinf(_Value);
		}

		__inline static float MATH_API FastSin0(const soDegrees& _Angle)																											/*!< Funcion Rapida: Retorna el seno en grados euler */
		{
			return sinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastSin1(const soDegrees& _Angle)																											/*!	< Funcion Rapida: Retorna el seno con mas precision en grados euler */
		{
			return sinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastSin0(const soRadians& _Angle)																											/*!< Funcion Rapida: Retorna el seno en radianes */
		{
			return sinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastSin1(const soRadians& _Angle)																											/*!< Funcion Rapida: Retorna el seno con mas precision en radianes */
		{
			return sinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastCos0(float _Value)																														/*!< Funcion Rapida: Retorna el coseno en float, no se garantiza que sea en grados euler o radianes */
		{
			return cosf(_Value);
		}

		__inline static float MATH_API FastCos1(float _Value) 																													/*!< Funcion Rapida: Retorna el coseno con mas precision en float, no se garantiza que sea en grados euler o radianes */
		{
			return cosf(_Value);
		}

		__inline static float MATH_API FastCos0(const soDegrees& _Angle)																											/*!< Funcion Rapida: Retorna el coseno en grados euler */
		{
			return cosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastCos1(const soDegrees& _Angle) 																											/*!< Funcion Rapida: Retorna el coseno con mas precision en grados euler */
		{	
			return cosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastCos0(const soRadians& _Angle)																											/*!< Funcion Rapida: Retorna el coseno en radianes */
		{
			return cosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastCos1(const soRadians& _Angle) 																											/*!< Funcion Rapida: Retorna el coseno con mas precision en radianes */
		{
			return cosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan0(float _Value) 																													/*!< Funcion Rapida: Retorna el tangente en float, no se garantiza que sea en grados euler o radianes */
		{
			return tanf(_Value);
		}

		__inline static float MATH_API FastTan1(float _Value) 																													/*!< Funcion Rapida: Retorna el tangente con mas precision en float, no se garantiza que sea en grados euler o radianes */
		{
			return tanf(_Value);
		}

		__inline static float MATH_API FastTan0(const soDegrees& _Angle) 																											/*!< Funcion Rapida: Retorna el tangente en grados euler */
		{
			return tanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan1(const soDegrees& _Angle) 																											/*!< Funcion Rapida: Retorna el tangente con mas precision en grados euler */
		{
			return tanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan0(const soRadians& _Angle) 																											/*!< Funcion Rapida: Retorna el tangente en radianes */
		{
			return tanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan1(const soRadians& _Angle) 																											/*!< Funcion Rapida: Retorna el tangente con mas precision en radianes */
		{
			return tanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcSin0(float _Value)																													/*!< Funcion Rapida: Retorna el arcoseno en float, no se garantiza que sea en grados euler o radianes */
		{
			return asinf(_Value);
		}

		__inline static float MATH_API FastArcSin1(float _Value)																													/*!< Funcion Rapida: Retorna el arcoseno con mas precision en float, no se garantiza que sea en grados euler o radianes */
		{
			return asinf(_Value);
		}

		__inline static float MATH_API FastArcSin0(const soDegrees& _Angle)																										/*!< Funcion Rapida: Retorna el arcoseno en grados euler */
		{
			return asinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcSin1(const soDegrees& _Angle)																										/*!< Funcion Rapida: Retorna el arcoseno con mas precision en grados euler */
		{
			return asinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcSin0(const soRadians& _Angle)																										/*!< Funcion Rapida: Retorna el arcoseno en radianes */
		{
			return asinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcSin1(const soRadians& _Angle)																										/*!< Funcion Rapida: Retorna el arcoseno con mas precision en radianes */
		{
			return asinf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcCos0(float _Value)																													/*!< Funcion Rapida: Retorna el arcocoseno en float, no se garantiza que sea en grados euler o radianes */
		{
			return acosf(_Value);
		}

		__inline static float MATH_API FastArcCos1(float _Value)																													/*!< Funcion Rapida: Retorna el arcocoseno con mas precision en float, no se garantiza que sea en grados euler o radianes */
		{
			return acosf(_Value);
		}

		__inline static float MATH_API FastArcCos0(const soDegrees& _Angle)																										/*!< Funcion Rapida: Retorna el arcocoseno en grados euler */
		{
			return acosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcCos1(const soDegrees& _Angle)																										/*!< Funcion Rapida: Retorna el arcocoseno con mas precision en grados euler */
		{
			return acosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcCos0(const soRadians& _Angle)																										/*!< Funcion Rapida: Retorna el arcocoseno en radianes */
		{
			return acosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcCos1(const soRadians& _Angle)																										/*!< Funcion Rapida: Retorna el arcocoseno con mas precision en radianes */
		{
			return acosf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcTan0(float _Value)																													/*!< Funcion Rapida: Retorna el arcotangente en float, no se garantiza que sea en grados euler o radianes */
		{
			return atanf(_Value);
		}

		__inline static float MATH_API FastArcTan1(float _Value)	 																												/*!< Funcion Rapida: Retorna el arcotangente con mas precision en float, no se garantiza que sea en grados euler o radianes */
		{
			return atanf(_Value);
		}

		__inline static float MATH_API FastArcTan0(const soDegrees& _Angle)																										/*!< Funcion Rapida: Retorna el arcotangente en grados euler */
		{
			return atanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcTan1(const soDegrees& _Angle)																										/*!< Funcion Rapida: Retorna el arcotangente con mas precision en grados euler */
		{
			return atanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcTan0(const soRadians& _Angle)																										/*!< Funcion Rapida: Retorna el arcotangente en radianes */
		{
			return atanf(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcTan1(const soRadians& _Angle)																										/*!< Funcion Rapida: Retorna el arcotangente con mas precision en radianes */
		{
			return atanf(_Angle.GetRadians());
		}

		/************************************************************************/
		/* Funciones de colision entre primitivas basicas                       */
		/************************************************************************/
		__inline static bool MATH_API IntersectRecttoRect(const soRect& _Rect1, const soRect& _Rect2)																			/*!< Verifica colicion entre 2 Rect */
		{
			//The sides of the rectangles
			int leftA, leftB;
			int rightA, rightB;
			int topA, topB;
			int bottomA, bottomB;

			//Calculate the sides of rect A
			leftA = _Rect1.X;
			rightA = _Rect1.X + _Rect1.m_Width;
			topA = _Rect1.Y;
			bottomA = _Rect1.Y + _Rect1.m_Height;

			//Calculate the sides of rect B
			leftB = _Rect2.X;
			rightB = _Rect2.X + _Rect2.m_Width;
			topB = _Rect2.Y;
			bottomB = _Rect2.Y + _Rect2.m_Height;

			//If any of the sides from A are outside of B
			if (bottomA <= topB)
			{
				return false;
			}

			if (topA >= bottomB)
			{
				return false;
			}

			if (rightA <= leftB)
			{
				return false;
			}

			if (leftA >= rightB)
			{
				return false;
			}

			//If none of the sides from A are outside B
			return true;
		}

		__inline static bool MATH_API IntersectRecttoPoint(const soRect& _Rect, const soPoint& _Point)																			/*!< Verifica colicion entre un punto y un Rect */
		{
			int leftA;
			int rightA;
			int topA;
			int bottomA;

			leftA = _Rect.X;
			rightA = _Rect.X + _Rect.m_Width;
			topA = _Rect.Y;
			bottomA = _Rect.Y + _Rect.m_Height;

			if (bottomA <= _Point.Y)
			{
				return false;
			}

			if (topA >= _Point.Y)
			{
				return false;
			}

			if (rightA <= _Point.X)
			{
				return false;
			}

			if (leftA >= _Point.X)
			{
				return false;
			}

			return true;
		}

		__inline static bool MATH_API IntersectPlanetoPlane(const soPlane& _Plane1, const soPlane& _Plane2)																		/*!< Colision entre Plano-Plano */
		{
			//Calculo de la direccion de la linea de interseccion
			soVector3D DirectionOfIntersectionLine = CrossProduct(_Plane1.m_Normal, _Plane2.m_Normal);

			//Si es 0, los planos son paralelos y separados o coincidentes, entonces se concideran como intersectados
			if (DotProduct(DirectionOfIntersectionLine, DirectionOfIntersectionLine) > EPSILON)
			{
				return true;
			}
			return false;
		}

		__inline static bool MATH_API IntersectPlanetoSphere(const soPlane& _Plane, const soSphere& _Sphere)																		/*!< Colision entre Plano-Esfera */
		{
			//Calculamos la distancia de la esfera al plano
			soVector3D PlaneNormalUnit = _Plane.m_Normal;
			NormalizeVector(PlaneNormalUnit);
			float fDist = DotProduct(PlaneNormalUnit, _Sphere.m_SphereCenter) - _Plane.m_W;

			//Si el centro de la esfera es +/- radio del plano, el plano intersecta la esfera
			if (Abs(fDist) <= _Sphere.m_fRadius)
			{
				return true;
			}
			return false;
		}

		__inline static bool MATH_API IntersectPlanetoRay(const soPlane& _Plane, const soRay& _Ray)																					/*!< Colision entre Plano-Rayo */
		{
			//Escalamos el vector direccion
			soVector3D Ray = soVector3D(_Ray.m_VecDirection) * MAX_FLOAT32;

			//Calculamos el valor t (de la direccion del rayo hacia el plano)
			float t = (_Plane.m_W - DotProduct(_Plane.m_Normal, _Ray.m_VecOrigin)) / DotProduct(_Plane.m_Normal, Ray);

			//Si el valor de t oscila entre 0 y 1, significa que hay interseccion, 
			//por lo que calculamos el punto y retornamos 
			if (t >= 0.0f && t <= 1.0f)
			{

				return true;
			}
			return false;
		}

		__inline static bool MATH_API IntersectPlanetoAABB(const soPlane& _Plane, const soAABB& _AABB)																			/*!< Colision entre Plano-AABB */
		{
			return IntersectAABBtoPlane(_AABB, _Plane);
		}

		__inline static bool MATH_API IntersectSpheretoSphere(const soSphere& _Sphere1, const soSphere& _Sphere2)																	/*!< Colision entre Esfera-Esfera */
		{
			//Calculamos la distancia cuadrada entre ambos centros
			soVector3D Distance = soVector3D(_Sphere1.m_SphereCenter) - soVector3D(_Sphere2.m_SphereCenter);
			float fSquareDistance = DotProduct(Distance, Distance);

			//las esferas intersectan si la suma de los radios al cuadrado son menores a la distancia cuadratica obtenida
			float fSquareRadius = Square(_Sphere1.m_fRadius + _Sphere2.m_fRadius);

			if (fSquareDistance <= fSquareRadius)
			{
				return true;
			}
			return false;
		}

		__inline static bool MATH_API IntersectSpheretoPlane(const soSphere& _Sphere, const soPlane& _Plane)																		/*!< Colision entre Esfera-Plano */
		{
			return IntersectPlanetoSphere(_Plane, _Sphere);
		}

		__inline static bool MATH_API IntersectSpheretoRay(const soSphere& _Sphere, const soRay& _Ray)																			/*!< Colision entre Esfera-Rayo */
		{
			soVector3D Distance = soVector3D(_Ray.m_VecOrigin) - soVector3D(_Sphere.m_SphereCenter);
			float b = DotProduct(Distance, _Ray.m_VecDirection);
			float c = DotProduct(Distance, Distance) - (Square(_Sphere.m_fRadius));

			//Salimos si el origen del rayo esta fuera de la esfera (c>0) & apunta hacia una direccion distinta (b>0)
			if (c > 0.0f && b > 0.0f)
			{
				return false;
			}

			//Calculamos el discriminante
			float fDiscriminant = Square(b) - c;

			//Si el rayo no impacta la esfera, el discriminante es negativo
			if (fDiscriminant < 0.0f)
			{
				return false;
			}

			//El rayo entonces esta en interseccion hacia la esfera, por lo que calculamos el punto de impacto
			return true;
		}

		__inline static bool MATH_API IntersectSpheretoAABB(const soSphere& _Sphere, const soAABB& _AABB)																			/*!< Colision entre Esfera-AABB */
		{
			return IntersectAABBtoSphere(_AABB, _Sphere);
		}

		__inline static bool MATH_API IntersectRaytoPlane(const soRay& _Ray, const soPlane& _Plane)													/*!< Colision entre Rayo-Plano */
		{
			return IntersectPlanetoRay(_Plane, _Ray);
		}

		__inline static bool MATH_API IntersectRaytoSphere(const soRay& _Ray, const soSphere& _Sphere)																			/*!< Colision entre Rayo-Esfera */
		{
			return IntersectSpheretoRay(_Sphere, _Ray);
		}

		__inline static bool MATH_API IntersectRaytoAABB(const soRay& _Ray, const soAABB& _AABB)																					/*!< Colision entre Rayo-AABB */
		{
			return IntersectAABBtoRay(_AABB, _Ray);
		}

		__inline static bool MATH_API IntersectAABBtoAABB(const soAABB& _AABB1, const soAABB& _AABB2)																				/*!< Colision entre AABB-AABB */
		{
			if (_AABB1.m_AABBMax.X < _AABB2.m_AABBMin.X || _AABB1.m_AABBMin.X > _AABB2.m_AABBMax.X) return false;
			if (_AABB1.m_AABBMax.Y < _AABB2.m_AABBMin.Y || _AABB1.m_AABBMin.Y > _AABB2.m_AABBMax.Y) return false;
			if (_AABB1.m_AABBMax.Z < _AABB2.m_AABBMin.Z || _AABB1.m_AABBMin.Z > _AABB2.m_AABBMax.Z) return false;

			return true;
		}

		__inline static bool MATH_API IntersectAABBtoPlane(const soAABB& _AABB, const soPlane& _Plane)																			/*!< Colision entre AABB-Plano */
		{
			//Calculamos la proyeccion del radio de intervalo del AABB en L(t) = b.c+t*p.n
			float fRadius = Vector3DLength(soVector3D(_AABB.m_AABBMax) - soVector3D(_AABB.m_AABBCenter));

			//Calculamos la distancia del centro de la caja al plano
			float fDistance = DotProduct(_Plane.m_Normal, _AABB.m_AABBCenter) - _Plane.m_W;

			//La interseccion ocurre cuando la distancia queda en el intervalo [-r,r]
			if (Abs(fDistance) <= fRadius && Abs(fDistance) >= -fRadius)
			{
				return true;
			}
			return false;
		}

		__inline static bool MATH_API IntersectAABBtoSphere(const soAABB& _AABB, const soSphere& _Sphere)																			/*!< Colision entre AABB-Esfera */
		{
			//Calculamos el punto minimo y maximo de la caja
			soVector3D AABBMax = _AABB.m_AABBMax;
			soVector3D AABBMin = _AABB.m_AABBMin;

			//Calculamos la distancia cuadrada entre el centro de la esfera y el AABB
			float fSquareDistance = 0.0f;

			for (unsigned int i = 0; i < 3; i++)
			{//Para cada axis cuenta cualquier exceso de distancia fuera de los limites de la caja
				float v = soVector3D(_Sphere.m_SphereCenter)[i];

				if (v < AABBMin[i])
				{
					fSquareDistance += Square(AABBMin[i] - v);
				}

				if (v > AABBMax[i])
				{
					fSquareDistance += Square(v - AABBMax[i]);
				}
			}

			//la esfera y el AABB intersectan si la distancia cuadrada entre ellos es menor al cuadrado del radio
			if (fSquareDistance <= Square(_Sphere.m_fRadius))
			{
				return true;
			}
			return false;
		}

		__inline static bool MATH_API IntersectAABBtoRay(const soAABB& _AABB, const soRay& _Ray)																					/*!< Colision entre AABB-Rayo */
		{
			soVector3D T_1, T_2; // vectors to hold the T-values for every direction
			float t_near = -MAX_FLOAT32; // maximums defined in float.h
			float t_far = MAX_FLOAT32;

			for (unsigned int i = 0; i < 3; i++)
			{ //we test slabs in every direction
				if (soVector3D(_Ray.m_VecDirection)[i] == 0)
				{ // ray parallel to planes in this direction
					if ((soVector3D(_Ray.m_VecOrigin)[i] < soVector3D(_AABB.m_AABBMin)[i]) || (soVector3D(_Ray.m_VecOrigin)[i] > soVector3D(_AABB.m_AABBMax)[i]))
					{
						return false; // parallel AND outside box : no intersection possible
					}
				}
				else
				{ // ray not parallel to planes in this direction
					T_1[i] = (soVector3D(_AABB.m_AABBMin)[i] - soVector3D(_Ray.m_VecOrigin)[i]) / soVector3D(_Ray.m_VecDirection)[i];
					T_2[i] = (soVector3D(_AABB.m_AABBMax)[i] - soVector3D(_Ray.m_VecOrigin)[i]) / soVector3D(_Ray.m_VecDirection)[i];

					if (T_1[i] > T_2[i])
					{ // we want T_1 to hold values for intersection with near plane
						Swap(T_1, T_2);
					}
					if (T_1[i] > t_near)
					{
						t_near = T_1[i];
					}
					if (T_2[i] < t_far)
					{
						t_far = T_2[i];
					}
					if ((t_near > t_far) || (t_far < 0))
					{
						return false;
					}
				}
			}
			return true; // if we made it here, there was an intersection - YAY
		}

		/************************************************************************/
		/* Funciones matematicas que involucran un Vector 2D como componente	*/
		/* principal                                                            */
		/************************************************************************/
	public:
		__inline static void MATH_API RotateVector(soVector2D& _Vector2D, float _Radians)																							/*!< Rotacion del Vector con Radianes */
		{
			float fRotationX = (_Vector2D.X * Cos(_Radians) - (_Vector2D.Y * Sin(_Radians)));
			float fRotationY = (_Vector2D.Y * Cos(_Radians) + (_Vector2D.X * Sin(_Radians)));

			_Vector2D.X = fRotationX;
			_Vector2D.Y = fRotationY;
		}

		__inline static void MATH_API RotateVector(soVector2D& _Vector2D, const soRadians& _Angle)																				/*!< Rotacion del Vector con Radianes */
		{
			RotateVector(_Vector2D, _Angle.GetRadians());
		}

		__inline static void MATH_API RotateVector(soVector2D& _Vector2D, const soDegrees& _Angle)																				/*!< Rotacion del Vector con Grados euler */
		{
			RotateVector(_Vector2D, _Angle.GetRadians());
		}

		__inline static float MATH_API Vector2DLength(const soVector2D& _Vector2D)																								/*!< Retorna la magnitud de un vector 2D */
		{
			return Sqrt(Square(_Vector2D.X) + Square(_Vector2D.Y));
		}

		__inline static float MATH_API Vector2DSquareLength(const soVector2D& _Vector2D)																							/*!< Retorna la magnitud de un vector 2D */
		{
			return Square(_Vector2D.X) + Square(_Vector2D.Y);
		}

		__inline static void MATH_API NormalizeVector(soVector2D& _Vector2D)																										/*!< Retorna una vercion unitaria del vector ingresado */
		{
			float fMagnitude = Vector2DLength(_Vector2D);

			if (fMagnitude != 0.0f)
			{
				_Vector2D /= fMagnitude;
			}
		}

		__inline static float MATH_API DotProduct(const soVector2D& _Vector2D1, const soVector2D& _Vector2D2)																		/*!< Retorna el escalar del producto punto entre 2 vectores */
		{
			return (_Vector2D1.X*_Vector2D2.X) + (_Vector2D1.Y*_Vector2D2.Y);
		}

		__inline static void MATH_API EscalateVector(soVector2D& _Vector2D, float _MaxValue)																						/*!< Retorna la vercion escalada de un vector a una magnitud maxima */
		{
			NormalizeVector(_Vector2D);

			_Vector2D *= _MaxValue;
		}

		__inline static void MATH_API TruncateVector(soVector2D& _Vector2D, float _MaxValue)																						/*!< Retorna una vercion truncada a una magnitud maxima del vector */
		{
			float fMagnitude = Vector2DSquareLength(_Vector2D);
			if (fMagnitude > Square(_MaxValue))
			{
				EscalateVector(_Vector2D, _MaxValue);
			}
		}

		/************************************************************************/
		/* Funciones matematicas que involucran un Vector 3D como componente	*/
		/* principal                                                            */
		/************************************************************************/
	public:
		__inline static void MATH_API RotateVector(soVector3D& _Vector3D, float _Radians, eAxis _Axis)																			/*!< Rotacion del Vector con Radianes */
		{
			soMatrix3x3 RotationMatrix;
			RotationMatrix = RotationMatrix3x3(_Radians, _Axis);

			_Vector3D = _Vector3D * RotationMatrix;
		}

		__inline static void MATH_API RotateVector(soVector3D& _Vector3D, const soRadians& _Angle, eAxis _Axis)																	/*!< Rotacion del Vector con Radianes */
		{
			RotateVector(_Vector3D, _Angle.GetRadians(), _Axis);
		}

		__inline static void MATH_API RotateVector(soVector3D& _Vector3D, const soDegrees& _Angle, eAxis _Axis)																	/*!< Rotacion del Vector con Grados euler */
		{
			RotateVector(_Vector3D, _Angle.GetRadians(), _Axis);
		}

		__inline static float MATH_API Vector3DLength(const soVector3D& _Vector3D)																								/*!< Retorna la magnitud del vector 3D */
		{
			return Sqrt(Square(_Vector3D.X) + Square(_Vector3D.Y) + Square(_Vector3D.Z));
		}

		__inline static float MATH_API Vector3DSquareLength(const soVector3D& _Vector3D)																							/*!< Retorna la magnitud de un vector 3D */
		{
			return Square(_Vector3D.X) + Square(_Vector3D.Y) + Square(_Vector3D.Z);
		}

		__inline static void MATH_API NormalizeVector(soVector3D& _Vector3D)																										/*!< Retorna una vercion unitaria del vector ingresado */
		{
			float fLength = Vector3DLength(_Vector3D);

			if (fLength != 0.0f)
			{
				_Vector3D /= fLength;
			}
		}

		__inline static float MATH_API DotProduct(const soVector3D& _Vector3D1, const soVector3D& _Vector3D2)																		/*!< Retorna el escalar del producto punto entre 2 vectores */
		{
			return((_Vector3D1.X*_Vector3D2.X) + (_Vector3D1.Y*_Vector3D2.Y) + (_Vector3D1.Z*_Vector3D2.Z));
		}

		__inline static soVector3D MATH_API CrossProduct(const soVector3D& _Vector3D1, const soVector3D& _Vector3D2)																/*!< Retorna el producto cruz entre dos vectores */
		{
			return soVector3D(_Vector3D1.Y * _Vector3D2.Z - _Vector3D1.Z * _Vector3D2.Y,
							_Vector3D1.Z * _Vector3D2.X - _Vector3D1.X * _Vector3D2.Z,
							_Vector3D1.X * _Vector3D2.Y - _Vector3D1.Y * _Vector3D2.X);
		}

		__inline static void MATH_API EscalateVector(soVector3D& _Vector3D, float _MaxValue)																						/*!< Retorna la vercion escalada de un vector a una magnitud maxima */
		{
			NormalizeVector(_Vector3D);

			_Vector3D *= _MaxValue;
		}

		__inline static void MATH_API TruncateVector(soVector3D& _Vector3D, float _MaxValue)																						/*!< Retorna una vercion truncada a una magnitud maxima del vector */
		{
			float fMagnitude = Vector3DSquareLength(_Vector3D);

			if (fMagnitude > Square(_MaxValue))
			{
				EscalateVector(_Vector3D, _MaxValue);
			}
		}

		__inline static void MATH_API CalculateTriTangent(soVector3D& _Position1, soVector3D& _Position2, soVector3D& _Position3, soVector2D& _UV1, soVector2D& _UV2, soVector2D& _UV3, soVector3D& _OutNormal, soVector3D& _OutTangent, soVector3D& _OutBiNormal)
		{
			soVector3D side0 = _Position1 - _Position2;
			soVector3D side1 = _Position3 - _Position1;
			//Calculate face normal
			_OutNormal = CrossProduct(side1, side0);
			NormalizeVector(_OutNormal);
			//Now we use a formula to calculate the tangent.
			float deltaV0 = _UV1.Y - _UV2.Y;
			float deltaV1 = _UV3.Y - _UV1.Y;
			_OutTangent = side0 * deltaV1 - side1 * deltaV0;
			NormalizeVector(_OutTangent);
			//Calculate binormal
			float deltaU0 = _UV1.X - _UV2.X;
			float deltaU1 = _UV3.X - _UV1.X;
			_OutBiNormal = side0 * deltaU1 - side1 * deltaU0;
			NormalizeVector(_OutBiNormal);
			//Now, we take the cross product of the tangents to get a vector which should point in the same direction as our normal calculated above.
			//If it points in the opposite direction (the dot product between the normals is less than zero), then we need to reverse the s and t tangents.
			//This is because the triangle has been mirrored when going from tangent space to object space.
			soVector3D tangentCross = CrossProduct(_OutTangent, _OutBiNormal);
			//Reverse tangents if necessary.
			if (DotProduct(tangentCross, _OutNormal) < 0.0f)
			{
				_OutTangent = _OutTangent * -1.0f;
				_OutBiNormal = _OutBiNormal * -1.0f;
			}
		}

		/************************************************************************/
		/* Funciones matematicas que involucran un Vector 4D como componente	*/
		/* principal                                                            */
		/************************************************************************/
	public:
		__inline static void MATH_API RotateVector(soVector4D& _Vector4D, float _Radians, eAxis _Axis)																			/*!< Retorna un vector4D rotado en el eje especificado */
		{
			soMatrix4x4 RotationMatrix;
			RotationMatrix = RotationMatrix4x4(_Radians, _Axis);

			_Vector4D = _Vector4D * RotationMatrix;
		}
		
		__inline static void MATH_API RotateVector(soVector4D& _Vector4D, const soRadians& _Angle, eAxis _Axis)																	/*!< Retorna un vector4D rotado en el eje especificado */
		{
			RotateVector(_Vector4D, _Angle.GetRadians(), _Axis);
		}
			
		__inline static void MATH_API RotateVector(soVector4D& _Vector4D, const soDegrees& _Angle, eAxis _Axis)																	/*!< Retorna un vector4D rotado en el eje especificado */
		{
			RotateVector(_Vector4D, _Angle.GetRadians(), _Axis);
		}

		__inline static float MATH_API Vector4DLength(const soVector4D& _Vector4D)																								/*!< Retorna la magnitud de un vector 3D */
		{
			return Sqrt(Square(_Vector4D.X) + Square(_Vector4D.Y) + Square(_Vector4D.Z) + Square(_Vector4D.W));
		}

		__inline static float MATH_API Vector4DSquareLength(const soVector4D& _Vector4D)																							/*!< Retorna la magnitud de un vector 3D */
		{
			return Square(_Vector4D.X) + Square(_Vector4D.Y) + Square(_Vector4D.Z) + Square(_Vector4D.W);
		}

		__inline static void MATH_API NormalizeVector(soVector4D& _Vector4D)																										/*!< Retorna una vercion unitaria del vector ingresado */
		{
			float fLength = Vector4DLength(_Vector4D);

			if (fLength != 0.0f)
			{
				_Vector4D /= fLength;
			}
		}

		__inline static float MATH_API DotProduct(const soVector4D& _Vector4D1, const soVector4D& _Vector4D2)																		/*!< Retorna el escalar del producto punto entre 2 vectores */
		{
			return((_Vector4D1.X*_Vector4D2.X) + (_Vector4D1.Y*_Vector4D2.Y) + (_Vector4D1.Z*_Vector4D2.Z) + (_Vector4D1.W*_Vector4D2.W));
		}

		__inline static soVector4D MATH_API CrossProduct(const soVector4D& _Vector4D1, const soVector4D& _Vector4D2)																/*!< Retorna el producto cruz entre dos vectores */
		{
			soVector4D Result = CrossProduct(soVector3D(_Vector4D1), soVector3D(_Vector4D2));
			Result.W = 1.0f;
			return Result;
		}

		__inline static void MATH_API EscalateVector(soVector4D& _Vector4D, float _MaxValue)																						/*!< Retorna la vercion escalada de un vector a una magnitud maxima */
		{
			NormalizeVector(_Vector4D);

			_Vector4D *= _MaxValue;
		}

		__inline static void MATH_API TruncateVector(soVector4D& _Vector4D, float _MaxValue)																						/*!< Retorna una vercion truncada a una magnitud maxima del vector */
		{
			float fMagnitude = Vector4DSquareLength(_Vector4D);
			if (fMagnitude > Square(_MaxValue))
			{
				EscalateVector(_Vector4D, _MaxValue);
			}
		}

		/************************************************************************/
		/* Funciones matematicas que involucran un Quaternion como componente	*/
		/* principal                                                            */
		/************************************************************************/
	private:
		__inline static void Multiply(soQuaternion& _Quaternion, soQuaternion _QuatFactor)
		{
			SetToProduct(_Quaternion, _QuatFactor, _Quaternion);
		}
		
		__inline static void SetToProduct(soQuaternion& _Quaternion, const	soQuaternion& _QuatLeft, const soQuaternion&	_QuatRight)
		{
			if ((&_Quaternion == &_QuatLeft) || (&_Quaternion == &_QuatRight))
			{
				soQuaternion quatTarget;

				quatTarget.X = _QuatLeft.W * _QuatRight.X + _QuatLeft.X * _QuatRight.W + _QuatLeft.Y * _QuatRight.Z - _QuatLeft.Z * _QuatRight.Y;
				quatTarget.Y = _QuatLeft.W * _QuatRight.Y + _QuatLeft.Y * _QuatRight.W + _QuatLeft.Z * _QuatRight.X - _QuatLeft.X * _QuatRight.Z;
				quatTarget.Z = _QuatLeft.W * _QuatRight.Z + _QuatLeft.Z * _QuatRight.W + _QuatLeft.X * _QuatRight.Y - _QuatLeft.Y * _QuatRight.X;
				quatTarget.W = _QuatLeft.W * _QuatRight.W - _QuatLeft.X * _QuatRight.X - _QuatLeft.Y * _QuatRight.Y - _QuatLeft.Z * _QuatRight.Z;

				_Quaternion.X = quatTarget.X;
				_Quaternion.Y = quatTarget.Y;
				_Quaternion.Z = quatTarget.Z;
				_Quaternion.W = quatTarget.W;
			}
			else
			{
				_Quaternion.X = _QuatLeft.W * _QuatRight.X + _QuatLeft.X * _QuatRight.W + _QuatLeft.Y * _QuatRight.Z - _QuatLeft.Z * _QuatRight.Y;
				_Quaternion.Y = _QuatLeft.W * _QuatRight.Y + _QuatLeft.Y * _QuatRight.W + _QuatLeft.Z * _QuatRight.X - _QuatLeft.X * _QuatRight.Z;
				_Quaternion.Z = _QuatLeft.W * _QuatRight.Z + _QuatLeft.Z * _QuatRight.W + _QuatLeft.X * _QuatRight.Y - _QuatLeft.Y * _QuatRight.X;
				_Quaternion.W = _QuatLeft.W * _QuatRight.W - _QuatLeft.X * _QuatRight.X - _QuatLeft.Y * _QuatRight.Y - _QuatLeft.Z * _QuatRight.Z;
			}
		}

		__inline static void ReverseMultiply(soQuaternion& _Quaternion, const soQuaternion& _QuatPrefix)
		{
			SetToProduct(_Quaternion, _QuatPrefix, _Quaternion);
		}

	public:
		__inline static soQuaternion MATH_API QuaternionConjugate(const soQuaternion& _Quaternion)																				/*!< Retorna el quaternion conjugado (aquel que representa el desplazamiento angular) */
		{
			return soQuaternion(
				-_Quaternion.X,
				-_Quaternion.Y,
				-_Quaternion.Z,
				_Quaternion.W);
		}

		__inline static soQuaternion MATH_API QuaternionInverse(const soQuaternion& _Quaternion)																				/*!< Retorna el inverso del cuaternion */
		{
			const float n = Square(_Quaternion.X) + Square(_Quaternion.Y) * Square(_Quaternion.Z);

			return soQuaternion(-_Quaternion.X / n, -_Quaternion.Y / n, -_Quaternion.Z / n, _Quaternion.W / n);
		}

		__inline static float MATH_API QuaternionLength(const soQuaternion& _Quaternion)																							/*!< Retorna la magnitud del quaternion */
		{
			return Sqrt(Square(_Quaternion.X) + Square(_Quaternion.Y) + Square(_Quaternion.Z) + Square(_Quaternion.W));
		}

		__inline static float MATH_API QuaternionSquareLength(const soQuaternion& _Quaternion)																					/*!< Retorna la magnitud cuadreada del quaternion */
		{
			return Square(_Quaternion.X) + Square(_Quaternion.Y) + Square(_Quaternion.Z) + Square(_Quaternion.W);
		}

		__inline static void MATH_API NormalizeQuaternion(soQuaternion& _Quaternion)																								/*!< Normaliza el quaternion. La perdida de datos puede estar presente */							
		{
			float fLength = QuaternionLength(_Quaternion);

			if (fLength != 0.0f)
			{
				_Quaternion *= 1.0f / fLength;
			}
		}

		__inline static float MATH_API DotProduct(const soQuaternion& _Quaternion1, const soQuaternion& _Quaternion2)															/*!< Retorna el producto punto entre 2 quaterniones */
		{
			return _Quaternion1.X * _Quaternion2.X + _Quaternion1.Y * _Quaternion2.Y + _Quaternion1.Z * _Quaternion2.Z + _Quaternion1.W * _Quaternion2.W;
		}

		__inline static soQuaternion MATH_API QuaternionLerp(const soQuaternion& _From, const soQuaternion& _To, float _T)														/*!< Retorna un cuaternion intermedio entre 2 deacuerdo al porsentaje */
		{
			soQuaternion From = _From;
			soQuaternion To = _To;

			float scale = 1.0f - _T;
			return soQuaternion((From*scale) + (To*_T));
		}

		__inline static soQuaternion MATH_API QuaternionSLerp(const soQuaternion& _From, const soQuaternion& _To, float _T, float threshold = 0.05f)							/*!< Retorna un quaternion intermedio entre 2, de forma smotheada */
		{
			soQuaternion From = _From;
			soQuaternion To = _To;

			float angle = DotProduct(From, To);

			// make sure we use the short rotation
			if (angle < 0.0f)
			{
				From = From * -1.0f;
				angle *= -1.0f;
			}

			if (angle <= (1.0f - threshold)) // spherical interpolation
			{
				const float theta = ArcCos(angle);
				const float invsintheta = 1.0f / (Sin(theta));
				const float scale = Sin(theta * (1.0f - _T)) * invsintheta;
				const float invscale = Sin(theta * _T) * invsintheta;
				return soQuaternion((From*scale) + (To*invscale));
			}
			else // linear interploation
			{
				return QuaternionLerp(From, To, _T);
			}
		}

		__inline static void MATH_API QuaternionToMatrixRotation3x3(const soQuaternion& _Quaternion, soMatrix3x3& _RotationMatrixOut)											/*!< Retorna una matriz de rotacion a partir de un Quaternion */
		{
			_RotationMatrixOut.fMatrix[0] = 1.0f - 2.0f*_Quaternion.Y*_Quaternion.Y - 2.0f*_Quaternion.Z*_Quaternion.Z;
			_RotationMatrixOut.fMatrix[1] = 2.0f*_Quaternion.X*_Quaternion.Y + 2.0f*_Quaternion.Z*_Quaternion.W;
			_RotationMatrixOut.fMatrix[2] = 2.0f*_Quaternion.X*_Quaternion.Z - 2.0f*_Quaternion.Y*_Quaternion.W;

			_RotationMatrixOut.fMatrix[3] = 2.0f*_Quaternion.X*_Quaternion.Y - 2.0f*_Quaternion.Z*_Quaternion.W;
			_RotationMatrixOut.fMatrix[4] = 1.0f - 2.0f*_Quaternion.X*_Quaternion.X - 2.0f*_Quaternion.Z*_Quaternion.Z;
			_RotationMatrixOut.fMatrix[5] = 2.0f*_Quaternion.Z*_Quaternion.Y + 2.0f*_Quaternion.X*_Quaternion.W;

			_RotationMatrixOut.fMatrix[6] = 2.0f*_Quaternion.X*_Quaternion.Z + 2.0f*_Quaternion.Y*_Quaternion.W;
			_RotationMatrixOut.fMatrix[7] = 2.0f*_Quaternion.Z*_Quaternion.Y - 2.0f*_Quaternion.X*_Quaternion.W;
			_RotationMatrixOut.fMatrix[8] = 1.0f - 2.0f*_Quaternion.X*_Quaternion.X - 2.0f*_Quaternion.Y*_Quaternion.Y;
		}

		__inline static void MATH_API QuaternionToMatrixRotation4x4(const soQuaternion& _Quaternion, soMatrix4x4& _RotationMatrixOut)											/*!< Retorna una matriz de rotacion a partir de un Quaternion */
		{
			_RotationMatrixOut.fMatrix[0] = 1.0f - 2.0f*_Quaternion.Y*_Quaternion.Y - 2.0f*_Quaternion.Z*_Quaternion.Z;
			_RotationMatrixOut.fMatrix[1] = 2.0f*_Quaternion.X*_Quaternion.Y + 2.0f*_Quaternion.Z*_Quaternion.W;
			_RotationMatrixOut.fMatrix[2] = 2.0f*_Quaternion.X*_Quaternion.Z - 2.0f*_Quaternion.Y*_Quaternion.W;
			_RotationMatrixOut.fMatrix[3] = 0.0f;

			_RotationMatrixOut.fMatrix[4] = 2.0f*_Quaternion.X*_Quaternion.Y - 2.0f*_Quaternion.Z*_Quaternion.W;
			_RotationMatrixOut.fMatrix[5] = 1.0f - 2.0f*_Quaternion.X*_Quaternion.X - 2.0f*_Quaternion.Z*_Quaternion.Z;
			_RotationMatrixOut.fMatrix[6] = 2.0f*_Quaternion.Z*_Quaternion.Y + 2.0f*_Quaternion.X*_Quaternion.W;
			_RotationMatrixOut.fMatrix[7] = 0.0f;

			_RotationMatrixOut.fMatrix[8] = 2.0f*_Quaternion.X*_Quaternion.Z + 2.0f*_Quaternion.Y*_Quaternion.W;
			_RotationMatrixOut.fMatrix[9] = 2.0f*_Quaternion.Z*_Quaternion.Y - 2.0f*_Quaternion.X*_Quaternion.W;
			_RotationMatrixOut.fMatrix[10] = 1.0f - 2.0f*_Quaternion.X*_Quaternion.X - 2.0f*_Quaternion.Y*_Quaternion.Y;
			_RotationMatrixOut.fMatrix[11] = 0.0f;

			_RotationMatrixOut.fMatrix[12] = 0.0f;
			_RotationMatrixOut.fMatrix[13] = 0.0f;
			_RotationMatrixOut.fMatrix[14] = 0.0f;
			_RotationMatrixOut.fMatrix[15] = 1.f;
		}

		__inline static void MATH_API QuaternionToEulerAngle(const soQuaternion& _Quaternion, soDegrees& _YawOut, soDegrees& _PichOut, soDegrees& _RollOut)						/*!< Retorna 3 angulos de rotacion a partir de un quaternion */
		{
			//Primero hacemos una matriz de rotacion a partir del quaternion 
			soMatrix4x4 Result = IdentityMatrix4x4();
			float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

			x2 = _Quaternion.X + _Quaternion.X;
			y2 = _Quaternion.Y + _Quaternion.Y;
			z2 = _Quaternion.Z + _Quaternion.Z;
			xx = _Quaternion.X * x2;
			xy = _Quaternion.X * y2;
			xz = _Quaternion.X * z2;
			yy = _Quaternion.Y * y2;
			yz = _Quaternion.Y * z2;
			zz = _Quaternion.Z * z2;
			wx = _Quaternion.W * x2;
			wy = _Quaternion.W * y2;
			wz = _Quaternion.W * z2;

			Result.Line[0][0] = 1.0f - (yy + zz);
			Result.Line[0][1] = xy + wz;
			Result.Line[0][2] = xz - wy;

			Result.Line[1][0] = xy - wz;
			Result.Line[1][1] = 1.0f - (xx + zz);
			Result.Line[1][2] = yz + wx;

			Result.Line[2][0] = xz + wy;
			Result.Line[2][1] = yz - wx;
			Result.Line[2][2] = 1.0f - (xx + yy);

			float fSinX = -Result.Line[2][1];

			_PichOut = soRadians(ArcSin(fSinX)).GetDegrees();

			float	fSinY, fSinZ, fCosY, fCosZ;

			if (1.0f - fabs(fSinX) > EPSILON)			// Gimbal lock?
			{
				fCosY = Result.Line[2][2];
				fSinY = Result.Line[2][0];
				_YawOut = soRadians(ArcTan2(fSinY, fCosY)).GetDegrees();

				fCosZ = Result.Line[1][1];
				fSinZ = Result.Line[0][1];
				_RollOut = soRadians(ArcTan2(fSinZ, fCosZ)).GetDegrees();
			}
			else											// Gimbal lock has occurred
			{
				_YawOut = 0;							// Yaw is undefined; just fix it

				fCosZ = Result.Line[0][0];
				fSinZ = Result.Line[0][2] * fSinX;
				_RollOut = soRadians(ArcTan2(fSinZ, fCosZ)).GetDegrees();
			}
		}

		__inline static void MATH_API QuaternionToRadianAngle(const soQuaternion& _Quaternion, soRadians& _YawOut, soRadians& _PichOut, soRadians& _RollOut)						/*!< Retorna 3 angulos de rotacion a partir de un quaternion */
		{
			soDegrees Y, P, R;
			QuaternionToEulerAngle(_Quaternion, Y, P, R);

			_YawOut = Y.GetRadians();
			_PichOut = P.GetRadians();
			_RollOut = R.GetRadians();
		}

		__inline static void MATH_API QuaternionToAxisAngle(const soQuaternion& _Quaternion, soVector3D& _AxisOut, soDegrees& _EulerAngleOut)									/*!< Retorna un eje y un angulo de rotacion a partir del quaternion */
		{
			float	len;
			float one_over_len;

			len = _Quaternion.X * _Quaternion.X + _Quaternion.Y * _Quaternion.Y + _Quaternion.Z * _Quaternion.Z;

			if (len > 1e-6)
			{
				one_over_len = 1.0f / len;
				_AxisOut.X = _Quaternion.X * one_over_len;
				_AxisOut.Y = _Quaternion.Y * one_over_len;
				_AxisOut.Z = _Quaternion.Z * one_over_len;
				_EulerAngleOut = soRadians(2.0f * ArcCos(_Quaternion.W)).GetDegrees();
			}

			else
			{
				_EulerAngleOut = 0.0f;
				_AxisOut.X = _AxisOut.Y = 0.0f;
				_AxisOut.Z = 1.0f;
			}

			NormalizeVector(_AxisOut);
		}

		__inline static void MATH_API QuaternionToAxisAngle(const soQuaternion& _Quaternion, soVector3D& _AxisOut, soRadians& _RadianAngleOut)									/*!< Retorna un eje y un angulo de rotacion a partir del quaternion */
		{
			soDegrees Temp;
			QuaternionToAxisAngle(_Quaternion, _AxisOut, Temp);
			_RadianAngleOut = Temp.GetRadians();
		}

		__inline static void MATH_API QuaternionRotateAxisX(soQuaternion& _Quaternion, const soDegrees _Angle)																	/*!< Rotacion sobre el eje espacial global X */
		{
			Multiply(_Quaternion, soQuaternion(Sin(_Angle.GetRadians() * 0.5f), 0.0f, 0.0f, Cos(_Angle.GetRadians() * 0.5f)));
		}

		__inline static void MATH_API QuaternionRotateAxisY(soQuaternion& _Quaternion, const soDegrees _Angle)																	/*!< Rotacion sobre el eje espacial global Y */
		{
			Multiply(_Quaternion, soQuaternion(0.0f, Sin(_Angle.GetRadians() * 0.5f), 0.0f, Cos(_Angle.GetRadians() * 0.5f)));
		}

		__inline static void MATH_API QuaternionRotateAxisZ(soQuaternion& _Quaternion, const soDegrees _Angle)																	/*!< Rotacion sobre el eje espacial global Z */
		{
			Multiply(_Quaternion, soQuaternion(0.0f, 0.0f, Sin(_Angle.GetRadians() * 0.5f), Cos(_Angle.GetRadians() * 0.5f)));
		}

		__inline static void MATH_API QuaternionRotateAxisX(soQuaternion& _Quaternion, const soRadians _Angle)																	/*!< Rotacion sobre el eje espacial global X */
		{
			QuaternionRotateAxisX(_Quaternion, soDegrees(_Angle.GetDegrees()));
		}

		__inline static void MATH_API QuaternionRotateAxisY(soQuaternion& _Quaternion, const soRadians _Angle)																	/*!< Rotacion sobre el eje espacial global Y */
		{
			QuaternionRotateAxisY(_Quaternion, soDegrees(_Angle.GetDegrees()));
		}

		__inline static void MATH_API QuaternionRotateAxisZ(soQuaternion& _Quaternion, const soRadians _Angle)																	/*!< Rotacion sobre el eje espacial global Z */
		{
			QuaternionRotateAxisZ(_Quaternion, soDegrees(_Angle.GetDegrees()));
		}

		__inline static void MATH_API QuaternionRotateLocalAxisX(soQuaternion& _Quaternion, const soDegrees _Angle)																/*!< Rotacion sobre el eje espacial local X */
		{
			ReverseMultiply(_Quaternion, soQuaternion(Sin(_Angle.GetRadians() * 0.5f), 0.0f, 0.0f, Cos(_Angle.GetRadians() * 0.5f)));
		}

		__inline static void MATH_API QuaternionRotateLocalAxisY(soQuaternion& _Quaternion, const soDegrees _Angle)																/*!< Rotacion sobre el eje espacial local Y */
		{
			ReverseMultiply(_Quaternion, soQuaternion(0.0f, Sin(_Angle.GetRadians() * 0.5f), 0.0f, Cos(_Angle.GetRadians() * 0.5f)));
		}

		__inline static void MATH_API QuaternionRotateLocalAxisZ(soQuaternion& _Quaternion, const  soDegrees _Angle)																/*!< Rotacion sobre el eje espacial local Z */
		{
			ReverseMultiply(_Quaternion, soQuaternion(0.0f, 0.0f, Sin(_Angle.GetRadians() * 0.5f), Cos(_Angle.GetRadians() * 0.5f)));
		}

		__inline static void MATH_API QuaternionRotateLocalAxisX(soQuaternion& _Quaternion, const soRadians _Angle)																/*!< Rotacion sobre el eje espacial local X */
		{
			QuaternionRotateLocalAxisX(_Quaternion, soDegrees(_Angle.GetDegrees()));
		}

		__inline static void MATH_API QuaternionRotateLocalAxisY(soQuaternion& _Quaternion, const soRadians _Angle)																/*!< Rotacion sobre el eje espacial local Y */
		{
			QuaternionRotateLocalAxisY(_Quaternion, soDegrees(_Angle.GetDegrees()));
		}

		__inline static void MATH_API QuaternionRotateLocalAxisZ(soQuaternion& _Quaternion, const soRadians _Angle)																/*!< Rotacion sobre el eje espacial local Z */
		{
			QuaternionRotateLocalAxisZ(_Quaternion, soDegrees(_Angle.GetDegrees()));
		}

		/************************************************************************/
		/* Funciones matematicas que involucran un Matrix 3D como componente	*/
		/* principal                                                            */
		/************************************************************************/
	public:
		__inline static soMatrix3x3 MATH_API IdentityMatrix3x3()																													/*!< Retorna la matriz identidad */
		{
			soMatrix3x3 IdentityMatrix;

			IdentityMatrix.m00 = 1;
			IdentityMatrix.m11 = 1;
			IdentityMatrix.m22 = 1;

			return IdentityMatrix;
		}

		__inline static soMatrix4x4 MATH_API IdentityMatrix4x4()																													/*!< Retorna la matriz identidad */
		{
			soMatrix4x4 IdentityMatrix;

			IdentityMatrix.m00 = 1;
			IdentityMatrix.m11 = 1;
			IdentityMatrix.m22 = 1;
			IdentityMatrix.m33 = 1;

			return IdentityMatrix;
		}

		__inline static soMatrix3x3 MATH_API TransposeMatrix(const soMatrix3x3& _Matrix3x3)																						/*!< Retorna la matriz transpuesta sin modificar el valor interno de la matriz */
		{
			soMatrix3x3 TransposeMatrix3D;
			for (unsigned int i = 0; i < 3; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					TransposeMatrix3D.Line[j][i] = _Matrix3x3.Line[i][j];
				}
			}

			return TransposeMatrix3D;
		}

		__inline static soMatrix3x3 MATH_API ScalarMatrix3x3(float _X, float _Y, float _Z)																						/*!< Retorna una matriz de escalacion */
		{
			soMatrix3x3 ScalarMatrix;
			ScalarMatrix.m00 = _X;
			ScalarMatrix.m11 = _Y;
			ScalarMatrix.m22 = _Z;

			return ScalarMatrix;
		}

		__inline static soMatrix3x3 MATH_API ScalarMatrix3x3(const soVector3D& _Vector3D)																							/*!< Retorna una matriz de escalacion */
		{
			return ScalarMatrix3x3(_Vector3D.X, _Vector3D.Y, _Vector3D.Z);
		}

		__inline static soMatrix3x3 MATH_API RotationMatrix3x3(float _Radians, eAxis _Axis)																						/*!< Retorna una matriz de rotacion respecto al eje mencionado */
		{
			soMatrix3x3 RotationMatrix = IdentityMatrix3x3();

			float fPreCalcCos = Cos(_Radians);
			float fPreCalcSin = Sin(_Radians);

			if (_Axis == X_Axis)
			{
				RotationMatrix.m11 = fPreCalcCos;
				RotationMatrix.m12 = fPreCalcSin;
				RotationMatrix.m21 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (_Axis == Y_Axis)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m20 = fPreCalcSin;
				RotationMatrix.m02 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (_Axis == Z_Axis)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m01 = fPreCalcSin;
				RotationMatrix.m10 = -fPreCalcSin;
				RotationMatrix.m11 = fPreCalcCos;
			}

			return RotationMatrix;
		}

		__inline static soMatrix3x3 MATH_API RotationMatrix3x3(const soRadians& _Angle, eAxis _Axis)																				/*!< Retorna una matriz de rotacion respecto al eje mencionado */
		{
			return RotationMatrix3x3(_Angle.GetRadians(), _Axis);
		}

		__inline static soMatrix3x3 MATH_API RotationMatrix3x3(const soDegrees& _Angle, eAxis _Axis)																				/*!< Retorna una matriz de rotacion respecto al eje mencionado */
		{
			return RotationMatrix3x3(_Angle.GetRadians(), _Axis);
		}

		__inline static soMatrix3x3 MATH_API RotationAxis3x3(const soVector3D& _Direction, float _Radians)																		/*!< Retorna una matris de rotacion a partir de la direccion */
		{
			soVector3D v = _Direction;

			NormalizeVector(v);
			soMatrix3x3 Matrix = IdentityMatrix3x3();
			Matrix.m00 = (1.0f - cos(_Radians)) * v.X * v.X + cos(_Radians);
			Matrix.m10 = (1.0f - cos(_Radians)) * v.X * v.Y - sin(_Radians) * v.Z;
			Matrix.m20 = (1.0f - cos(_Radians)) * v.X * v.Z + sin(_Radians) * v.Y;
			Matrix.m01 = (1.0f - cos(_Radians)) * v.Y * v.X + sin(_Radians) * v.Z;
			Matrix.m11 = (1.0f - cos(_Radians)) * v.Y * v.Y + cos(_Radians);
			Matrix.m21 = (1.0f - cos(_Radians)) * v.Y * v.Z - sin(_Radians) * v.X;
			Matrix.m02 = (1.0f - cos(_Radians)) * v.Z * v.X - sin(_Radians) * v.Y;
			Matrix.m12 = (1.0f - cos(_Radians)) * v.Z * v.Y + sin(_Radians) * v.X;
			Matrix.m22 = (1.0f - cos(_Radians)) * v.Z * v.Z + cos(_Radians);

			return  Matrix;
		}

		__inline static soMatrix3x3 MATH_API RotationAxis3x3(const soVector3D& _Direction, const soDegrees& _Angle)																/*!< Retorna una matris de rotacion a partir de la direccion */
		{
			return RotationAxis3x3(_Direction, _Angle.GetRadians());
		}

		__inline static soMatrix3x3 MATH_API RotationAxis3x3(const soVector3D& _Direction, const soRadians& _Angle)																/*!< Retorna una matris de rotacion a partir de la direccion */
		{
			return RotationAxis3x3(_Direction, _Angle.GetRadians());
		}

		__inline static float MATH_API DeterminantMatrix3x3(const soMatrix3x3& _Matrix3x3)																						/*!< Retorna el determinante de la matriz */
		{
			return	((_Matrix3x3.m00 * _Matrix3x3.m11 * _Matrix3x3.m22) + (_Matrix3x3.m01 * _Matrix3x3.m12 * _Matrix3x3.m20) + (_Matrix3x3.m02 * _Matrix3x3.m10 * _Matrix3x3.m21)) -
					((_Matrix3x3.m02 * _Matrix3x3.m11 * _Matrix3x3.m20) + (_Matrix3x3.m01 * _Matrix3x3.m10 * _Matrix3x3.m22) + (_Matrix3x3.m00 * _Matrix3x3.m12 * _Matrix3x3.m21));
		}

		/************************************************************************/
		/* Funciones matematicas que involucran un Matrix 4D como componente	*/
		/* principal                                                            */
		/************************************************************************/
	public:
		//__inline static soMatrix4x4 MATH_API IdentityMatrix4x4()																													/*!< Retorna la matriz identidad */
		//{
		//	soMatrix4x4 IdentityMatrix;
		//	IdentityMatrix.m00 = 1;
		//	IdentityMatrix.m11 = 1;
		//	IdentityMatrix.m22 = 1;
		//	IdentityMatrix.m33 = 1;
		//	return IdentityMatrix;
		//}

		__inline static soMatrix4x4 MATH_API TransposeMatrix(const soMatrix4x4 & _Matrix4x4)																						/*!< Retorna la matriz transpuesta */
		{
			soMatrix4x4 TransposeMatrix;
			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					TransposeMatrix.Line[j][i] = _Matrix4x4.Line[i][j];
				}
			}

			return TransposeMatrix;
		}

		__inline static soMatrix4x4 MATH_API ScalarMatrix4x4(float _X, float _Y, float _Z)																						/*!< Retorna una matriz de escalacion */
		{
			soMatrix4x4 ScalarMatrix;
			ScalarMatrix.m00 = _X;
			ScalarMatrix.m11 = _Y;
			ScalarMatrix.m22 = _Z;
			ScalarMatrix.m33 = 1;

			return ScalarMatrix;
		}

		__inline static soMatrix4x4 MATH_API ScalarMatrix4x4(const soVector3D& _Vector3D)																							/*!< Retorna una matriz de escalacion */
		{
			return ScalarMatrix4x4(_Vector3D.X, _Vector3D.Y, _Vector3D.Z);
		}

		__inline static soMatrix4x4 MATH_API TranslationMatrix4x4(float _X, float _Y, float _Z)																					/*!< Retorna una matriz de traslacion */
		{
			soMatrix4x4 TranslationMatrix = IdentityMatrix4x4();
			TranslationMatrix.m03 = _X;
			TranslationMatrix.m13 = _Y;
			TranslationMatrix.m23 = _Z;

			return TranslationMatrix;
		}

		__inline static soMatrix4x4 MATH_API TranslationMatrix4x4(const soVector3D& _Vector4D)																					/*!< Retorna una matriz de traslacion */
		{
			return TranslationMatrix4x4(_Vector4D.X, _Vector4D.Y, _Vector4D.Z);
		}

		__inline static soMatrix4x4 MATH_API RotationMatrix4x4(float _Radians, eAxis _Axis)																						/*!< Retorna una matriz de rotacion */
		{
			soMatrix4x4 RotationMatrix = IdentityMatrix4x4();

			float fPreCalcCos = Cos(_Radians);
			float fPreCalcSin = Sin(_Radians);

			if (_Axis == X_Axis)
			{
				RotationMatrix.m11 = fPreCalcCos;
				RotationMatrix.m12 = fPreCalcSin;
				RotationMatrix.m21 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (_Axis == Y_Axis)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m20 = fPreCalcSin;
				RotationMatrix.m02 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (_Axis == Z_Axis)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m01 = fPreCalcSin;
				RotationMatrix.m10 = -fPreCalcSin;
				RotationMatrix.m11 = fPreCalcCos;
			}

			return soMatrix4x4(RotationMatrix);
		}

		__inline static soMatrix4x4 MATH_API RotationMatrix4x4(const soRadians& _Angle, eAxis _Axis)																				/*!< Retorna una matriz de rotacion */
		{
			return RotationMatrix4x4(_Angle.GetRadians(), _Axis);
		}

		__inline static soMatrix4x4 MATH_API RotationMatrix4x4(const soDegrees& _Angle, eAxis _Axis)																				/*!< Retorna una matriz de rotacion */
		{
			return RotationMatrix4x4(_Angle.GetRadians(), _Axis);
		}

		__inline static soMatrix4x4 MATH_API RotationAxis4x4(const soVector3D& _AxisVector, float _Radians)																		/*!< Retorna una matris de rotacion a partir del eje proporcionado */
		{
			soVector3D v = _AxisVector;

			NormalizeVector(v);
			soMatrix4x4 Matrix = IdentityMatrix4x4();
			Matrix.m00 = (1.0f - Cos(_Radians)) * v.X * v.X + Cos(_Radians);
			Matrix.m10 = (1.0f - Cos(_Radians)) * v.X * v.Y - Sin(_Radians) * v.Z;
			Matrix.m20 = (1.0f - Cos(_Radians)) * v.X * v.Z + Sin(_Radians) * v.Y;
			Matrix.m01 = (1.0f - Cos(_Radians)) * v.Y * v.X + Sin(_Radians) * v.Z;
			Matrix.m11 = (1.0f - Cos(_Radians)) * v.Y * v.Y + Cos(_Radians);
			Matrix.m21 = (1.0f - Cos(_Radians)) * v.Y * v.Z - Sin(_Radians) * v.X;
			Matrix.m02 = (1.0f - Cos(_Radians)) * v.Z * v.X - Sin(_Radians) * v.Y;
			Matrix.m12 = (1.0f - Cos(_Radians)) * v.Z * v.Y + Sin(_Radians) * v.X;
			Matrix.m22 = (1.0f - Cos(_Radians)) * v.Z * v.Z + Cos(_Radians);

			return  Matrix;
		}

		__inline static soMatrix4x4 MATH_API RotationAxis4x4(const soVector3D& _AxisVector, const soDegrees& _Angle)																/*!< Retorna una matris de rotacion a partir del eje proporcionado */
		{
			return RotationAxis4x4(_AxisVector, _Angle.GetRadians());
		}

		__inline static soMatrix4x4 MATH_API RotationAxis4x4(const soVector3D& _AxisVector, const soRadians& _Angle)																/*!< Retorna una matris de rotacion a partir del eje proporcionado */
		{
			return RotationAxis4x4(_AxisVector, _Angle.GetRadians());
		}

		__inline static soMatrix4x4 MATH_API MatrixLookAtLH(const soVector3D& _EyePosition, const soVector3D& _FocusPosition, const soVector3D& _UpDirection)						/*!< Retorna la matriz de proyeccion de mano izquierda a partir de la posicion y el punto objetivo */
		{
			//Direccion, que es una linea de ti al objeto, no esta perpendicular al vector y de vista
			soVector3D vDir, vRight, vUp, vOffset;
			vDir = soVector3D(_FocusPosition) - _EyePosition;
			NormalizeVector(vDir);

			//Perpendicularizar el vector vista hacia up y vista
			vRight = CrossProduct(_UpDirection, vDir);
			NormalizeVector(vRight);

			//Con esto, el productro cruz con derecha y arriva me da el nuevo vector arriva, que es perpendicular al vector que esta hacia el objeto
			vUp = CrossProduct(vDir, vRight);

			//Esta ultima transformacion terminara convirtiendo los objetos a mi origen, suponiendo que yo soy el origen
			//Esta en sentido contrario porque queremos que se conviertan hacia la camara, no al revez
			vOffset = soVector3D(-1.0f * DotProduct(vRight, _EyePosition), -1.0f * DotProduct(vUp, _EyePosition), -1.0f * DotProduct(vDir, _EyePosition));

			soMatrix4x4 MV;
			MV.m00 = vRight.X;
			MV.m10 = vRight.Y;
			MV.m20 = vRight.Z;
			MV.m30 = vOffset.X;

			MV.m01 = vUp.X;
			MV.m11 = vUp.Y;
			MV.m21 = vUp.Z;
			MV.m31 = vOffset.Y;

			MV.m02 = vDir.X;
			MV.m12 = vDir.Y;
			MV.m22 = vDir.Z;
			MV.m32 = vOffset.Z;

			MV.m03 = 0;
			MV.m13 = 0;
			MV.m23 = 0;
			MV.m33 = 1;

			return MV;
		}

		__inline static soMatrix4x4 MATH_API MatrixPerspectiveForLH(const soRadians _FovAngleY, float _AspectRatio, float _NearZ, float _FarZ)										/*!< Retorna la matriz de perspectiva */
		{
			//Vamos a comprimir, entre mas sea el angulo, metemos mas geometria a la pantalla
			soMatrix4x4 MP;

			//Cotagente
			float ctg = 1.0f / Tan(_FovAngleY.GetRadians() / 2.0f);

			MP.m00 = ctg / _AspectRatio;
			MP.m11 = ctg;

			//Nomalizamos eje Z
			MP.m22 = _FarZ / (_FarZ - _NearZ);
			MP.m32 = -_NearZ * _FarZ / (_FarZ - _NearZ);

			//z se transfiere a W
			MP.m23 = 1;

			return MP;
		}//FOV = angulo de perspectiva en radianes

		__inline static soMatrix4x4 MATH_API MatrixPerspectiveForLH(const soDegrees _FovAngleY, float _AspectRatio, float _NearZ, float _FarZ)										/*!< Retorna la matriz de perspectiva */
		{
			return MatrixPerspectiveForLH(soRadians(_FovAngleY), _AspectRatio, _NearZ, _FarZ);
		}//FOV = angulo de perspectiva en radianes

		__inline static float MATH_API DeterminantMatrix4x4(const soMatrix4x4 & _Matrix4x4)																							/*!< Retorna el determinante de la matriz */
		{
			return	_Matrix4x4.m03 * _Matrix4x4.m12 * _Matrix4x4.m21 * _Matrix4x4.m30 - _Matrix4x4.m02 * _Matrix4x4.m13 * _Matrix4x4.m21 * _Matrix4x4.m30 -
					_Matrix4x4.m03 * _Matrix4x4.m11 * _Matrix4x4.m22 * _Matrix4x4.m30 + _Matrix4x4.m01 * _Matrix4x4.m13 * _Matrix4x4.m22 * _Matrix4x4.m30 +
					_Matrix4x4.m02 * _Matrix4x4.m11 * _Matrix4x4.m23 * _Matrix4x4.m30 - _Matrix4x4.m01 * _Matrix4x4.m12 * _Matrix4x4.m23 * _Matrix4x4.m30 -
					_Matrix4x4.m03 * _Matrix4x4.m12 * _Matrix4x4.m20 * _Matrix4x4.m31 + _Matrix4x4.m02 * _Matrix4x4.m13 * _Matrix4x4.m20 * _Matrix4x4.m31 +
					_Matrix4x4.m03 * _Matrix4x4.m10 * _Matrix4x4.m22 * _Matrix4x4.m31 - _Matrix4x4.m00 * _Matrix4x4.m13 * _Matrix4x4.m22 * _Matrix4x4.m31 -
					_Matrix4x4.m02 * _Matrix4x4.m10 * _Matrix4x4.m23 * _Matrix4x4.m31 + _Matrix4x4.m00 * _Matrix4x4.m12 * _Matrix4x4.m23 * _Matrix4x4.m31 +
					_Matrix4x4.m03 * _Matrix4x4.m11 * _Matrix4x4.m20 * _Matrix4x4.m32 - _Matrix4x4.m01 * _Matrix4x4.m13 * _Matrix4x4.m20 * _Matrix4x4.m32 -
					_Matrix4x4.m03 * _Matrix4x4.m10 * _Matrix4x4.m21 * _Matrix4x4.m32 + _Matrix4x4.m00 * _Matrix4x4.m13 * _Matrix4x4.m21 * _Matrix4x4.m32 +
					_Matrix4x4.m01 * _Matrix4x4.m10 * _Matrix4x4.m23 * _Matrix4x4.m32 - _Matrix4x4.m00 * _Matrix4x4.m11 * _Matrix4x4.m23 * _Matrix4x4.m32 -
					_Matrix4x4.m02 * _Matrix4x4.m11 * _Matrix4x4.m20 * _Matrix4x4.m33 + _Matrix4x4.m01 * _Matrix4x4.m12 * _Matrix4x4.m20 * _Matrix4x4.m33 +
					_Matrix4x4.m02 * _Matrix4x4.m10 * _Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m00 * _Matrix4x4.m12 * _Matrix4x4.m21 * _Matrix4x4.m33 -
					_Matrix4x4.m01 * _Matrix4x4.m10 * _Matrix4x4.m22 * _Matrix4x4.m33 + _Matrix4x4.m00 * _Matrix4x4.m11 * _Matrix4x4.m22 * _Matrix4x4.m33;
		}
		__inline static soMatrix3x3 MATH_API invert(soMatrix3x3& _Matrix3x3)
		{
			float determinant, invDeterminant;
			float tmp[9];

			tmp[0] = _Matrix3x3.fMatrix[4] * _Matrix3x3.fMatrix[8] - _Matrix3x3.fMatrix[5] * _Matrix3x3.fMatrix[7];
			tmp[1] = _Matrix3x3.fMatrix[2] * _Matrix3x3.fMatrix[7] - _Matrix3x3.fMatrix[1] * _Matrix3x3.fMatrix[8];
			tmp[2] = _Matrix3x3.fMatrix[1] * _Matrix3x3.fMatrix[5] - _Matrix3x3.fMatrix[2] * _Matrix3x3.fMatrix[4];
			tmp[3] = _Matrix3x3.fMatrix[5] * _Matrix3x3.fMatrix[6] - _Matrix3x3.fMatrix[3] * _Matrix3x3.fMatrix[8];
			tmp[4] = _Matrix3x3.fMatrix[0] * _Matrix3x3.fMatrix[8] - _Matrix3x3.fMatrix[2] * _Matrix3x3.fMatrix[6];
			tmp[5] = _Matrix3x3.fMatrix[2] * _Matrix3x3.fMatrix[3] - _Matrix3x3.fMatrix[0] * _Matrix3x3.fMatrix[5];
			tmp[6] = _Matrix3x3.fMatrix[3] * _Matrix3x3.fMatrix[7] - _Matrix3x3.fMatrix[4] * _Matrix3x3.fMatrix[6];
			tmp[7] = _Matrix3x3.fMatrix[1] * _Matrix3x3.fMatrix[6] - _Matrix3x3.fMatrix[0] * _Matrix3x3.fMatrix[7];
			tmp[8] = _Matrix3x3.fMatrix[0] * _Matrix3x3.fMatrix[4] - _Matrix3x3.fMatrix[1] * _Matrix3x3.fMatrix[3];

			// check determinant if it is 0
			determinant = _Matrix3x3.fMatrix[0] * tmp[0] + _Matrix3x3.fMatrix[1] * tmp[3] + _Matrix3x3.fMatrix[2] * tmp[6];
			if (fabs(determinant) <= EPSILON)
			{
				return IdentityMatrix3x3(); // cannot inverse, make it idenety matrix
			}

			// divide by the determinant
			invDeterminant = 1.0f / determinant;
			_Matrix3x3.fMatrix[0] = invDeterminant * tmp[0];
			_Matrix3x3.fMatrix[1] = invDeterminant * tmp[1];
			_Matrix3x3.fMatrix[2] = invDeterminant * tmp[2];
			_Matrix3x3.fMatrix[3] = invDeterminant * tmp[3];
			_Matrix3x3.fMatrix[4] = invDeterminant * tmp[4];
			_Matrix3x3.fMatrix[5] = invDeterminant * tmp[5];
			_Matrix3x3.fMatrix[6] = invDeterminant * tmp[6];
			_Matrix3x3.fMatrix[7] = invDeterminant * tmp[7];
			_Matrix3x3.fMatrix[8] = invDeterminant * tmp[8];

			return _Matrix3x3;
		}

		__inline static soMatrix4x4 MATH_API invertAffine(soMatrix4x4& _Matrix4x4)
		{
			// R^-1
			soMatrix3x3 r(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10]);
			r = invert(r);
			_Matrix4x4.fMatrix[0] = r.fMatrix[0];  _Matrix4x4.fMatrix[1] = r.fMatrix[1];  _Matrix4x4.fMatrix[2] = r.fMatrix[2];
			_Matrix4x4.fMatrix[4] = r.fMatrix[3];  _Matrix4x4.fMatrix[5] = r.fMatrix[4];  _Matrix4x4.fMatrix[6] = r.fMatrix[5];
			_Matrix4x4.fMatrix[8] = r.fMatrix[6];  _Matrix4x4.fMatrix[9] = r.fMatrix[7];  _Matrix4x4.fMatrix[10] = r.fMatrix[8];

			// -R^-1 * T
			float x = _Matrix4x4.fMatrix[12];
			float y = _Matrix4x4.fMatrix[13];
			float z = _Matrix4x4.fMatrix[14];
			_Matrix4x4.fMatrix[12] = -(r.fMatrix[0] * x + r.fMatrix[3] * y + r.fMatrix[6] * z);
			_Matrix4x4.fMatrix[13] = -(r.fMatrix[1] * x + r.fMatrix[4] * y + r.fMatrix[7] * z);
			_Matrix4x4.fMatrix[14] = -(r.fMatrix[2] * x + r.fMatrix[5] * y + r.fMatrix[8] * z);

			// last row should be unchanged (0,0,0,1)
			//m[3] = m[7] = m[11] = 0.0f;
			//m[15] = 1.0f;

			return _Matrix4x4;
		}

		__inline static float  MATH_API getCofactor(float m0, float m1, float m2,
			float m3, float m4, float m5,
			float m6, float m7, float m8)
		{
			return m0 * (m4 * m8 - m5 * m7) -
				m1 * (m3 * m8 - m5 * m6) +
				m2 * (m3 * m7 - m4 * m6);
		}

		__inline static soMatrix4x4 MATH_API invertGeneral(soMatrix4x4& _Matrix4x4)
		{
			// get cofactors of minor matrices
			float cofactor0 = getCofactor(_Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[7], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10],_Matrix4x4.fMatrix[11], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[14], _Matrix4x4.fMatrix[15]);
			float cofactor1 = getCofactor(_Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[7], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[10],_Matrix4x4.fMatrix[11], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[14], _Matrix4x4.fMatrix[15]);
			float cofactor2 = getCofactor(_Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[7], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[11], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[15]);
			float cofactor3 = getCofactor(_Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[14]);

			// get determinant
			float determinant = _Matrix4x4.fMatrix[0] * cofactor0 - _Matrix4x4.fMatrix[1] * cofactor1 + _Matrix4x4.fMatrix[2] * cofactor2 - _Matrix4x4.fMatrix[3] * cofactor3;
			if (fabs(determinant) <= EPSILON)
			{
				return IdentityMatrix4x4();
			}

			// get rest of cofactors for adj(M)
			float cofactor4 = getCofactor(_Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10], _Matrix4x4.fMatrix[11],_Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[14], _Matrix4x4.fMatrix[15]);
			float cofactor6 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[11], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[15]);
			float cofactor7 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[14]);
			float cofactor5 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[10], _Matrix4x4.fMatrix[11],_Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[14], _Matrix4x4.fMatrix[15]);

			float cofactor8 = getCofactor(_Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[7], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[14], _Matrix4x4.fMatrix[15]);
			float cofactor9 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[7], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[14], _Matrix4x4.fMatrix[15]);
			float cofactor10 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[7], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[15]);
			float cofactor11 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[12], _Matrix4x4.fMatrix[13], _Matrix4x4.fMatrix[14]);

			float cofactor12 = getCofactor(_Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[7],_Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10], _Matrix4x4.fMatrix[11]);
			float cofactor13 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[6], _Matrix4x4.fMatrix[7],_Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[10], _Matrix4x4.fMatrix[11]);
			float cofactor14 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[3], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[7],_Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[11]);
			float cofactor15 = getCofactor(_Matrix4x4.fMatrix[0], _Matrix4x4.fMatrix[1], _Matrix4x4.fMatrix[2], _Matrix4x4.fMatrix[4], _Matrix4x4.fMatrix[5], _Matrix4x4.fMatrix[6],_Matrix4x4.fMatrix[8], _Matrix4x4.fMatrix[9], _Matrix4x4.fMatrix[10]);

			// build inverse matrix = adj(M) / det(M)
			// adjugate of M is the transpose of the cofactor matrix of M
			float invDeterminant = 1.0f / determinant;
			_Matrix4x4.fMatrix[0] = invDeterminant * cofactor0;
			_Matrix4x4.fMatrix[1] = -invDeterminant * cofactor4;
			_Matrix4x4.fMatrix[2] = invDeterminant * cofactor8;
			_Matrix4x4.fMatrix[3] = -invDeterminant * cofactor12;

			_Matrix4x4.fMatrix[4] = -invDeterminant * cofactor1;
			_Matrix4x4.fMatrix[5] = invDeterminant * cofactor5;
			_Matrix4x4.fMatrix[6] = -invDeterminant * cofactor9;
			_Matrix4x4.fMatrix[7] = invDeterminant * cofactor13;
		
			_Matrix4x4.fMatrix[8] = invDeterminant * cofactor2;
			_Matrix4x4.fMatrix[9] = -invDeterminant * cofactor6;
			_Matrix4x4.fMatrix[10] = invDeterminant * cofactor10;
			_Matrix4x4.fMatrix[11] = -invDeterminant * cofactor14;
		
			_Matrix4x4.fMatrix[12] = -invDeterminant * cofactor3;
			_Matrix4x4.fMatrix[13] = invDeterminant * cofactor7;
			_Matrix4x4.fMatrix[14] = -invDeterminant * cofactor11;
			_Matrix4x4.fMatrix[15] = invDeterminant * cofactor15;

			return _Matrix4x4;
		}

		__inline static soMatrix4x4 MATH_API MatrixInverse4x4(const soMatrix4x4& _Matrix4x4)																							/*!< Retorna una matriz inversa */
		{
			soMatrix4x4 tempMatrix = _Matrix4x4;

			// If the 4th row is [0,0,0,1] then it is affine matrix and
			// it has no projective transformation.
			if (_Matrix4x4.fMatrix[3] == 0 && _Matrix4x4.fMatrix[7] == 0 && _Matrix4x4.fMatrix[11] == 0 && _Matrix4x4.fMatrix[15] == 1)
				return invertAffine(tempMatrix);
			else
				return invertGeneral(tempMatrix);
			
			return soMatrix4x4();
		}
		
		__inline static soMatrix4x4 MATH_API ChangeHandCoordinateSystem(const soMatrix4x4& _Matrix4x4)
		{
			soMatrix4x4 tempMatrix = _Matrix4x4;
			tempMatrix.Line[3][2] *= -1;

			return tempMatrix;
		}

};
#if PLATFORM != WINDOWS_MATH
	typedef soPlatformMath soMath;
#endif
}



