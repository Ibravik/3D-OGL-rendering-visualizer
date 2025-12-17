/************************************************************************/
/**
* @LC	  1/16/2016
* @file   soWindowsMath.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   9/22/2015
* @brief  Declaration of specific platform math functions
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* inclucuion de archivos de cabecera necesarios para compilacion       */
/************************************************************************/
#include "soPlatformMath.h"

/************************************************************************/
/* Estructura de Funciones matematicas para plataforma Windows          */
/************************************************************************/
namespace SoulSDK
{
	struct WindowsMath : public soPlatformMath
	{
		__inline static float MATH_API Sin(float _Value)														/*!< Retorna el seno de en un float, no se garantiza que el valor devuelto sea en radianes o grados euler */
		{
			return sinf(_Value);
		}

		__inline static float MATH_API Sin(soDegrees& _Angle)												/*!< Retorna el seno en grados euler */
		{
			return sinf(_Angle.GetRadians());
		}

		__inline static float MATH_API Sin(soRadians& _Angle)												/*!< Retorna el seno en radianes */
		{
			return sinf(_Angle.GetRadians());
		}

		__inline static float MATH_API Cos(float _Value)														/*!< Retorna el coseno en un float, no se garantiza que sea en grados euler o radianes */
		{
			return cosf(_Value);
		}

		__inline static float MATH_API Cos(soDegrees& _Angle)												/*!< Retorna el coseno en grados euler */
		{
			return cosf(_Angle.GetRadians());
		}

		__inline static float MATH_API Cos(soRadians& _Angle)												/*!< Retorna el coseno en radianes */
		{
			return cosf(_Angle.GetRadians());
		}

		__inline static float MATH_API Tan(float _Value)														/*!< Retorna el Tan de un flotante, no se garantiza que sea en grados euler o radianes */
		{
			return tanf(_Value);
		}

		__inline static float MATH_API Tan(soDegrees& _Angle)												/*!< Retorna el Tan en grados euler */
		{
			return tanf(_Angle.GetRadians());
		}
			
		__inline static float MATH_API Tan(soRadians& _Angle)												/*!< Retorna el Tan en radianes */
		{
			return tanf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcSin(float _Value)													/*!< Retorna el Arcoseno de un flotante, no se garantiza que sea en grados euler o radianes */
		{
			return asinf(_Value);
		}

		__inline static float MATH_API ArcSin(soDegrees& _Angle)												/*!< Retorna el Arcoseno en grados euler */
		{
			return asinf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcSin(soRadians& _Angle)												/*!< Retorna el Arcoseno en radianes */
		{
			return asinf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcCos(float _Value)													/*!< Retorna el Arcocoseno de un flotante, no se garantiza que sea en grados euler o radianes */
		{
			return acosf(_Value);
		}

		__inline static float MATH_API ArcCos(soDegrees& _Angle)												/*!< Retorna el Arcocoseno en grados euler */
		{
			return acosf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcCos(soRadians& _Angle)												/*!< Retorna el Arcocoseno en radianes */
		{
			return acosf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcTan(float _Value)													/*!< Retorna el ArcoTangente de un flotante, no se garantiza que sea en grados euler o radianes */
		{
			return atanf(_Value);
		}

		__inline static float MATH_API ArcTan(soDegrees& _Angle)												/*!< Retorna el ArcoTangente en grados euler */
		{
			return atanf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcTan(soRadians& _Angle)												/*!< Retorna el ArcoTangente en radianes */
		{
			return atanf(_Angle.GetRadians());
		}

		__inline static float MATH_API ArcTan2(float _Value1, float _Value2)									/*!< Retorna el ArcoTangente en radianes */
		{
			return atan2f(_Value1, _Value2);
		}

		__inline static float MATH_API LogX(float _Value, float _Base)										/*!< Retorna el logaritmo base X de un flotante */
		{
			return logf(_Value) / logf(_Base);
		}

		__inline static float MATH_API LogN(float _Value)													/*!< Retorna el Logaritmo neperiano de un flotante */
		{
			return logf(_Value) / logf(2.0f);
		}

		__inline static float MATH_API LogE(float _Value)													/*!< Retorna el logaritmo natural */
		{
			return logf(_Value);
		}

		__inline static float MATH_API Sqrt(float _Value)													/*!< Retorna raiz cuadrada de un flotante */
		{
			return sqrtf(_Value);
		}

		__inline static float MATH_API Cbrt(float _Value)													/*!< Retorna raiz cubica de un flotante */
		{
			return cbrtf(_Value);
		}
			
		__inline static float MATH_API Pow(float _Value, float _Pow)											/*!< Retorna la potencia de un flotante */
		{
			return pow(_Value, _Pow);
		}

		__inline static float MATH_API Square(float _Value)													/*!< Retorna el cuadrado de un flotante */
		{
			return _Value*_Value;
		}

		__inline static float MATH_API InvSqrt(float _Value)													/*!< Retorna el inverso de la raiz cuadrada de un flotante */
		{
			return 1 / Sqrt(_Value);
		}

		__inline static float MATH_API Abs(float _Value)														/*!< Retorna el inverso de la raiz cuadrada de un flotante */
		{
			if (_Value < 0)
			{
				return -1 * _Value;
			}
			return _Value;
		}

		__inline static float MATH_API FastSin0(float _Value)												/*!< Funcion Rapida: Retorna el seno de un flotante, no se garantiza que sea en radianes o grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: X-X3/3!+x5/5!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 5 decimales

			float fSin = _Value;
			float fBasePow = Pow(_Value, 3.f);
			float fPow2 = Pow(_Value, 2.f);

			fSin -= 0.166666666667f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.008333333333f * fBasePow;

			return fSin;
		}

		__inline static float MATH_API FastSin1(float _Value)												/*!< Funcion Rapida: Retorna el seno con mas precision, no se garantiza que sea en radianes o grados euler  */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: X-X3/3!+x5/5!+....
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 5 decimales

			float fSin = _Value;
			float fBasePow = Pow(_Value, 3.f);
			float fPow2 = Pow(_Value, 2.f);

			fSin -= 0.166666666667f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.008333333333f * fBasePow;
			fBasePow *= fPow2;
			fSin -= 0.000198412698f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.000002755732f * fBasePow;
			fBasePow *= fPow2;
			fSin -= 0.000000025052f * fBasePow;

			return fSin;
		}

		__inline static float MATH_API FastSin0(soDegrees& _Angle)											/*!< Funcion Rapida: Retorna el seno en grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: X-X3/3!+x5/5!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 5 decimales

			float fSin = _Angle.GetRadians();
			float fBasePow = Pow(fSin, 3.f);
			float fPow2 = Pow(fSin, 2.f);

			fSin -= 0.166666666667f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.008333333333f * fBasePow;

			return fSin;
		}

		__inline static float MATH_API FastSin1(soDegrees& _Angle)											/*!	< Funcion Rapida: Retorna el seno con mas precision en grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: X-X3/3!+x5/5!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 5 decimales

			float fSin = _Angle.GetRadians();
			float fBasePow = Pow(fSin, 3.f);
			float fPow2 = Pow(fSin, 2.f);

			fSin -= 0.166666666667f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.008333333333f * fBasePow;
			fBasePow *= fPow2;
			fSin -= 0.000198412698f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.000002755732f * fBasePow;
			fBasePow *= fPow2;
			fSin -= 0.000000025052f * fBasePow;

			return fSin;
		}

		__inline static float MATH_API FastSin0(soRadians& _Angle)											/*!< Funcion Rapida: Retorna el seno con radianes */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: X-X3/3!+x5/5!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 5 decimales

			float fSin = _Angle.GetRadians();
			float fBasePow = Pow(fSin, 3.f);
			float fPow2 = Pow(fSin, 2.f);

			fSin -= 0.166666666667f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.008333333333f * fBasePow;

			return fSin;
		}

		__inline static float MATH_API FastSin1(soRadians& _Angle)											/*!< Funcion Rapida: Retorna el seno con mas precision en radianes */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: X-X3/3!+x5/5!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 5 decimales

			float fSin = _Angle.GetRadians();
			float fBasePow = Pow(fSin, 3.f);
			float fPow2 = Pow(fSin, 2.f);

			fSin -= 0.166666666667f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.008333333333f * fBasePow;
			fBasePow *= fPow2;
			fSin -= 0.000198412698f * fBasePow;
			fBasePow *= fPow2;
			fSin += 0.000002755732f * fBasePow;
			fBasePow *= fPow2;
			fSin -= 0.000000025052f * fBasePow;

			return fSin;
		}
		
		__inline static float MATH_API FastCos0(float _Value) 												/*!< Funcion Rapida: Retorna el coseno, no se garantiza que sea en radianes o grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: 1-X2/2!+x4/4!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 6 decimales

			float fCos = 1;
			float fBasePow = Pow(_Value, 2.f);
			float fPow2 = Pow(_Value, 2.f);

			fCos -= 0.500000000000f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.041666666667f * fBasePow;

			return fCos;
		}

		__inline static float MATH_API FastCos1(float _Value) 												/*!< Funcion Rapida: Retorna el coseno con mas precision, no se garantiza que sea en radianes o grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: 1-X2/2!+x4/4!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 6 decimales

			float fCos = 1;
			float fBasePow = Pow(_Value, 2.f);
			float fPow2 = Pow(_Value, 2.f);

			fCos -= 0.500000000000f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.041666666667f * fBasePow;
			fBasePow *= fPow2;
			fCos -= 0.001388888889f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.000024801587f * fBasePow;
			fBasePow *= fPow2;
			fCos -= 0.000000275573f * fBasePow;

			return fCos;
		}

		__inline static float MATH_API FastCos0(soDegrees& _Angle) 											/*!< Funcion Rapida: Retorna el coseno en grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: 1-X2/2!+x4/4!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 6 decimales

			float fCos = 1;
			float fBasePow = Pow(_Angle.GetRadians(), 2.f);
			float fPow2 = Pow(_Angle.GetRadians(), 2.f);

			fCos -= 0.500000000000f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.041666666667f * fBasePow;

			return fCos;
		}

		__inline static float MATH_API FastCos1(soDegrees& _Angle) 											/*!< Funcion Rapida: Retorna el coseno con mas precision en grados euler */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: 1-X2/2!+x4/4!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 6 decimales

			float fCos = 1;
			float fBasePow = Pow(_Angle.GetRadians(), 2.f);
			float fPow2 = Pow(_Angle.GetRadians(), 2.f);

			fCos -= 0.500000000000f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.041666666667f * fBasePow;
			fBasePow *= fPow2;
			fCos -= 0.001388888889f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.000024801587f * fBasePow;
			fBasePow *= fPow2;
			fCos -= 0.000000275573f * fBasePow;

			return fCos;
		}

		__inline static float MATH_API FastCos0(soRadians& _Angle) 											/*!< Funcion Rapida: Retorna el coseno en radianes */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: 1-X2/2!+x4/4!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 6 decimales

			float fCos = 1;
			float fBasePow = Pow(_Angle.GetRadians(), 2.f);
			float fPow2 = Pow(_Angle.GetRadians(), 2.f);

			fCos -= 0.500000000000f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.041666666667f * fBasePow;

			return fCos;
		}

		__inline static float MATH_API FastCos1(soRadians& _Angle) 											/*!< Funcion Rapida: Retorna el coseno con mas precision en radianes */
		{
			//La forma del polinomio desarrollada para valores >= 0 es: 1-X2/2!+x4/4!+.... 
			//por lo tanto, en la resolucion se usa la inversa precalculada
			//La diferencia entre la funcion precisa y la rapida es de 6 decimales

			float fCos = 1;
			float fBasePow = Pow(_Angle.GetRadians(), 2.f);
			float fPow2 = Pow(_Angle.GetRadians(), 2.f);

			fCos -= 0.500000000000f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.041666666667f * fBasePow;
			fBasePow *= fPow2;
			fCos -= 0.001388888889f * fBasePow;
			fBasePow *= fPow2;
			fCos += 0.000024801587f * fBasePow;
			fBasePow *= fPow2;
			fCos -= 0.000000275573f * fBasePow;

			return fCos;
		}
		
		__inline static float MATH_API FastTan0(float _Value)												/*!< Funcion Rapida: Retorna el tangente, no se garantiza que sea en radianes o grados euler */
		{
			//Por medio de identidades trigonometricas, sabemos que tan= sin/Cos, por lo tanto...
			return FastSin0(_Value) / FastCos0(_Value);
		}

		__inline static float MATH_API FastTan1(float _Value) 												/*!< Funcion Rapida: Retorna el tangente con mas precision, no se garantiza que sea en radianes o grados euler */
		{
			//Por medio de identidades trigonometricas, sabemos que tan= sin/Cos, por lo tanto...
			return FastSin1(_Value) / FastCos1(_Value);
		}

		__inline static float MATH_API FastTan0(soDegrees& _Angle) 											/*!< Funcion Rapida: Retorna el tangente en grados euler */
		{
			//Por medio de identidades trigonometricas, sabemos que tan= sin/Cos, por lo tanto...
			return FastSin0(_Angle.GetRadians()) / FastCos0(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan1(soDegrees& _Angle) 											/*!< Funcion Rapida: Retorna el tangente con mas precision en grados euler */
		{
			//Por medio de identidades trigonometricas, sabemos que tan= sin/Cos, por lo tanto...
			return FastSin1(_Angle.GetRadians()) / FastCos1(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan0(soRadians& _Angle)											/*!< Funcion Rapida: Retorna el tangente en radianes */
		{
			//Por medio de identidades trigonometricas, sabemos que tan= sin/Cos, por lo tanto...
			return FastSin0(_Angle.GetRadians()) / FastCos0(_Angle.GetRadians());
		}

		__inline static float MATH_API FastTan1(soRadians& _Angle) 											/*!< Funcion Rapida: Retorna el tangente con mas precision en radianes */
		{
			//Por medio de identidades trigonometricas, sabemos que tan= sin/Cos, por lo tanto...
			return FastSin1(_Angle.GetRadians()) / FastCos1(_Angle.GetRadians());
		}

		__inline static float MATH_API FastArcSin0(float _Value)												/*!< Funcion Rapida: Retorna el arcoseno, no se garantiza que sea en radianes o grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcSin = _Value;
			float fBasePow = powf(_Value, 3.f);
			float fPow = powf(_Value, 2.f);

			fArcSin += 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.075000000000f * fBasePow;

			return fArcSin;
		}

		__inline static float MATH_API FastArcSin1(float _Value)												/*!< Funcion Rapida: Retorna el arcoseno con mas precision, no se garantiza que sea en radianes o grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcSin = _Value;
			float fBasePow = powf(_Value, 3.f);
			float fPow = powf(_Value, 2.f);

			fArcSin += 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.075000000000f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.044642857143f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.030381944444f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.022372159091f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.017352764423f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.013964843750f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.011551800896f * fBasePow;

			return fArcSin;
		}

		__inline static float MATH_API FastArcSin0(soDegrees& _Angle)										/*!< Funcion Rapida: Retorna el arcoseno en grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcSin = _Angle.GetRadians();
			float fBasePow = powf(fArcSin, 3.f);
			float fPow = powf(fArcSin, 2.f);

			fArcSin += 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.075000000000f * fBasePow;

			return fArcSin;
		}

		__inline static float MATH_API FastArcSin1(soDegrees& _Angle)										/*!< Funcion Rapida: Retorna el arcoseno con mas precision en grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcSin = _Angle.GetRadians();
			float fBasePow = powf(fArcSin, 3.f);
			float fPow = powf(fArcSin, 2.f);

			fArcSin += 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.075000000000f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.044642857143f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.030381944444f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.022372159091f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.017352764423f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.013964843750f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.011551800896f * fBasePow;

			return fArcSin;
		}

		__inline static float MATH_API FastArcSin0(soRadians& _Angle)										/*!< Funcion Rapida: Retorna el arcoseno conen radianes */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcSin = _Angle.GetRadians();
			float fBasePow = powf(fArcSin, 3.f);
			float fPow = powf(fArcSin, 2.f);

			fArcSin += 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.075000000000f * fBasePow;

			return fArcSin;
		}

		__inline static float MATH_API FastArcSin1(soRadians& _Angle)										/*!< Funcion Rapida: Retorna el arcoseno con mas precision en radianes */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcSin = _Angle.GetRadians();
			float fBasePow = powf(fArcSin, 3.f);
			float fPow = powf(fArcSin, 2.f);

			fArcSin += 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.075000000000f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.044642857143f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.030381944444f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.022372159091f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.017352764423f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.013964843750f * fBasePow;
			fBasePow *= fPow;
			fArcSin += 0.011551800896f * fBasePow;

			return fArcSin;
		}

		__inline static float MATH_API FastArcCos0(float _Value)												/*!< Funcion Rapida: Retorna el arcocoseno, no se garantiza que sea en radianes o grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcCos = HALF_PI;
			float fBasePow = powf(_Value, 3.f);
			float fPow = powf(_Value, 2.f);

			fArcCos -= 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.075000000000f * fBasePow;

			return fArcCos;
		}

		__inline static float MATH_API FastArcCos1(float _Value)												/*!< Funcion Rapida: Retorna el arcocoseno con mas precision, no se garantiza que sea en radianes o grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcCos = HALF_PI;
			float fBasePow = powf(_Value, 3.f);
			float fPow = powf(_Value, 2.f);

			fArcCos -= 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.075000000000f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.044642857143f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.030381944444f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.022372159091f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.017352764423f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.013964843750f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.011551800896f * fBasePow;

			return fArcCos;
		}

		__inline static float MATH_API FastArcCos0(soDegrees& _Angle)										/*!< Funcion Rapida: Retorna el arcocoseno en grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcCos = HALF_PI;
			float fBasePow = powf(_Angle.GetRadians(), 3.f);
			float fPow = powf(_Angle.GetRadians(), 2.f);

			fArcCos -= 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.075000000000f * fBasePow;

			return fArcCos;
		}

		__inline static float MATH_API FastArcCos1(soDegrees& _Angle)										/*!< Funcion Rapida: Retorna el arcocoseno con mas precision en grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcCos = HALF_PI;
			float fBasePow = powf(_Angle.GetRadians(), 3.f);
			float fPow = powf(_Angle.GetRadians(), 2.f);

			fArcCos -= 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.075000000000f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.044642857143f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.030381944444f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.022372159091f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.017352764423f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.013964843750f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.011551800896f * fBasePow;

			return fArcCos;
		}

		__inline static float MATH_API FastArcCos0(soRadians& _Angle)										/*!< Funcion Rapida: Retorna el arcocoseno en radianes */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcCos = HALF_PI;
			float fBasePow = powf(_Angle.GetRadians(), 3.f);
			float fPow = powf(_Angle.GetRadians(), 2.f);

			fArcCos -= 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.075000000000f * fBasePow;

			return fArcCos;
		}
		__inline static float MATH_API FastArcCos1(soRadians& _Angle)										/*!< Funcion Rapida: Retorna el arcocoseno con mas precision en radianes */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcCos = HALF_PI;
			float fBasePow = powf(_Angle.GetRadians(), 3.f);
			float fPow = powf(_Angle.GetRadians(), 2.f);

			fArcCos -= 0.166666666667f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.075000000000f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.044642857143f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.030381944444f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.022372159091f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.017352764423f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.013964843750f * fBasePow;
			fBasePow *= fPow;
			fArcCos -= 0.011551800896f * fBasePow;

			return fArcCos;
		}

		__inline static float MATH_API FastArcTan0(float _Value)												/*!< Funcion Rapida: Retorna el arcotangente, no se garantiza que sea en radianes o grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcTan = _Value;
			float fBasePow = powf(_Value, 3.f);
			float fPow = powf(_Value, 2.f);

			fArcTan -= 0.333333333333f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.200000000000f * fBasePow;

			return fArcTan;
		}

		__inline static float MATH_API FastArcTan1(float _Value)												/*!< Funcion Rapida: Retorna el arcotangente con mas precision, no se garantiza que sea en radianes o grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcTan = _Value;
			float fBasePow = powf(_Value, 3.f);
			float fPow = powf(_Value, 2.f);

			fArcTan -= 0.333333333333f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.200000000000f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.142857142857f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.111111111111f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.09090909090f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.076923076923f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.066666666667f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.058823529412f * fBasePow;

			return fArcTan;
		}

		__inline static float MATH_API FastArcTan0(soDegrees& _Angle)										/*!< Funcion Rapida: Retorna el arcotangente en grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcTan = _Angle.GetRadians();
			float fBasePow = powf(fArcTan, 3.f);
			float fPow = powf(fArcTan, 2.f);

			fArcTan -= 0.333333333333f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.200000000000f * fBasePow;

			return fArcTan;
		}

		__inline static float MATH_API FastArcTan1(soDegrees& _Angle)										/*!< Funcion Rapida: Retorna el arcotangente con mas precision en grados euler */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcTan = _Angle.GetRadians();
			float fBasePow = powf(fArcTan, 3.f);
			float fPow = powf(fArcTan, 2.f);

			fArcTan -= 0.333333333333f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.200000000000f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.142857142857f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.111111111111f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.09090909090f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.076923076923f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.066666666667f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.058823529412f * fBasePow;

			return fArcTan;
		}

		__inline static float MATH_API FastArcTan0(soRadians& _Angle)										/*!< Funcion Rapida: Retorna el arcotangente en radianes */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcTan = _Angle.GetRadians();
			float fBasePow = powf(fArcTan, 3.f);
			float fPow = powf(fArcTan, 2.f);

			fArcTan -= 0.333333333333f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.200000000000f * fBasePow;

			return fArcTan;
		}

		__inline static float MATH_API FastArcTan1(soRadians& _Angle)										/*!< Funcion Rapida: Retorna el arcotangente con mas precision en radianes */
		{
			//La precision de la operacion es hasta el 6to decimal
			float fArcTan = _Angle.GetRadians();
			float fBasePow = powf(fArcTan, 3.f);
			float fPow = powf(fArcTan, 2.f);

			fArcTan -= 0.333333333333f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.200000000000f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.142857142857f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.111111111111f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.09090909090f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.076923076923f * fBasePow;
			fBasePow *= fPow;
			fArcTan -= 0.066666666667f * fBasePow;
			fBasePow *= fPow;
			fArcTan += 0.058823529412f * fBasePow;

			return fArcTan;
		}
	};
#if PLATFORM == WINDOWS_MATH
	typedef WindowsMath soMath;
#endif
}
