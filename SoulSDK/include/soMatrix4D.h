/************************************************************************/
/**
* @LC	  9/16/2016
* @file   soMatrix4D.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   10/18/2015
* @brief  Declaration of class soMatrix4D
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once
#pragma warning(disable : 4201)

/************************************************************************/
/* Inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/
#include <Soul_StandardTools.h>

namespace SoulSDK
{
	/************************************************************************/
	/* Forward Class Declaration                                            */
	/************************************************************************/
	class soVector4D;

	/************************************************************************/
	/* Definicion de la clase soMatrix4D                                    */
	/************************************************************************/	
#pragma pack (push)
#pragma pack(16)
	class soMatrix4x4
	{
		/************************************************************************/
		/* Declaracion de estructura matrix			                            */
		/************************************************************************/
	public:
		union
		{			
			struct
			{				
				float	m00, m01, m02, m03,
						m10, m11, m12, m13,
						m20, m21, m22, m23,
						m30, m31, m32, m33;
			};
			struct
			{
				float	_11, _12, _13, _14,
						_21, _22, _23, _24,
						_31, _32, _33, _34,
						_41, _42, _43, _44;
			};
			float Line[4][4];
			float fMatrix[16];
		};

		/************************************************************************/
		/* Declaracion de construcctores y destructor                           */
		/************************************************************************/
	public:																	
		explicit soMatrix4x4(const float& _m00 = 0.0f, const float& _m01= 0.0f, const float& _m02= 0.0f, const float& _m03= 0.0f,
					const float& _m10 = 0.0f, const float& _m11= 0.0f, const float& _m12= 0.0f, const float& _m13= 0.0f,
					const float& _m20 = 0.0f, const float& _m21= 0.0f, const float& _m22= 0.0f, const float& _m23= 0.0f,
					const float& _m30 = 0.0f, const float& _m31= 0.0f, const float& _m32= 0.0f, const float& _m33= 0.0f) :
					m00(_m00), m01(_m01), m02(_m02), m03(_m03),
					m10(_m10), m11(_m11), m12(_m12), m13(_m13),
					m20(_m20), m21(_m21), m22(_m22), m23(_m23),
					m30(_m30), m31(_m31), m32(_m32), m33(_m33) {};								/*!< Constructor que solicita los 16 elementos por separado */
		soMatrix4x4(const float m0[4], const float m1[4], const float m2[4], const float m3[4]);/*!< Constructor que solicita 4 arreglos de 4 elementos */
		soMatrix4x4(const soMatrix4x4& _CopyObj);												/*!< Constructor que crea un objeto copia del objeto recibido*/

		~soMatrix4x4();																			/*!< Destructor de la clase */

		/************************************************************************/
		/* funciones de ayuda de la clase                                       */
		/************************************************************************/
	private:
		void ResetMatrix();																		/*!< Inicializa las variables de la matriz a 0 */
	public:
		//bool Equal(soMatrix4x4& _Matrix4x4, float _Precision);								/*!< Verifica si las matrices son equivalentes tomando en cuenta el grado de precision de math */
		bool Equal(const soMatrix4x4& _Matrix4x4, float _Precision);							/*!< Verifica si las matrices son equivalentes tomando en cuenta el grado de precision de math */
		soVector4D GetLine(unsigned int _value)const;											/*!< Retorna la fina segun el indice indicado */
		soVector4D GetColum(unsigned int _value)const;											/*!< Retorna la olumna segun el indice */

		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
	public:
		void operator=			(const soMatrix4x4& _Matrix4x4);								/*!< Igualacion binaria */
		soMatrix4x4 operator+	(const soMatrix4x4& _Matrix4x4);								/*!< Suma entre 2 Matrices4D */
		soMatrix4x4 operator-	(const soMatrix4x4& _Matrix4x4);								/*!< Resta entre 2 Matrices4D */
		soMatrix4x4 operator*	(const soMatrix4x4& _Matrix4x4);								/*!< Multiplicacion entre 2 matrices4D */
		soVector4D operator*	(const soVector4D& _Vector4D);									/*!< Multiplicacion entre 2 matrices (4x4 & 4x1) */
		soMatrix4x4 operator*	(const float& _Value);											/*!< Multiplicacion entre 1 matriz4D y un flotante */

		void operator+=	(const soMatrix4x4& _Matrix4x4);										/*!< Suma entre 2 matrices */
		void operator-=	(const soMatrix4x4& _Matrix4x4);										/*!< Resta entre 2 matrices */
		void operator*=	(const soMatrix4x4& _Matrix4x4);										/*!< Multiplicacion entre 2 matrices4D */
		void operator*=	(const float& _Value);													/*!< Multiplicacion entre 1 matriz4D y un flotante */

		bool operator==			(const soMatrix4x4& _Matrix4x4);								/*!< Comparacion positiva entre 2 matrices4D */
		bool operator!=			(const soMatrix4x4& _Matrix4x4);								/*!< Comparacion negativa entre 2 matrices4D */
	};
};
#pragma pack(pop)
#pragma warning(default : 4201)
