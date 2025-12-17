/********************************************************************/
/**
* LC	  4/10/2017		
* @file   dtCamera.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017	
* @brief  dtCamera class declaration. This class controll all the camera
		  changes, and rebuild the matrix for shaders
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header class inclution								                */
/************************************************************************/
#include <Soul_Math.h>

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* dtCamera data struct	                                                */
	/************************************************************************/
	struct CameraData
	{
		soVector3D Position;									/*!< Camera position */
		soVector3D Up;											/*!< Up vector */
		soVector3D Front;										/*!< Front */
		soDegrees Fov;											/*!< Fov */
		float AspectRatio;										/*!< Aspect ratio */
		float Near;												/*!< Near */
		float Far;												/*!< Far */
		soString CameraName;									/*!< Camera name */
		soDegrees MaxPitch;										/*!< Max pich angle */
		soVector3D MaxVel;										/*!< Max Camera Velocity */
		soVector3D RotationVel;									/*!< Max Camera Velocity rotation in euler */
		bool InvertY;											/*!< Invert camera y rotation */
		bool EnableUpMovement;									/*!< Enable movement on up vector */
		bool LockUp;											/*!< Lock the up direction */

		CameraData()
		{
			Position = soVector3D(0, 0, -10);
			Up = soVector3D(0, 1, 0);
			Front = soVector3D(0, 0, 1);
			Fov = 70.0f;
			AspectRatio = 21.0f / 9.0f;
			Near = 0.1f;
			Far = 300.0f;
			CameraName = TEXT("Default");
			MaxPitch = 89.0f;
			MaxVel = soVector4D(1, 1, 1, 0.1f);
			RotationVel = soVector3D(0.1f, 0.1f, 0.1f);
			InvertY = false;
			EnableUpMovement = false;
			LockUp = true;
		}
	};

	/************************************************************************/
	/* dtCamera	class declaration										    */
	/************************************************************************/
	class dtCamera
	{		
	public:
		dtCamera();											
		virtual ~dtCamera();								

		/************************************************************************/
		/* Variables									                        */
		/************************************************************************/
	private:
		soVector3D m_Velocity;									/*!< Velocity */
		soMatrix3x3 m_Rotation;									/*!< Rotation Matrix */
		soVector3D m_LookAt;									/*!< Objetive camera point */
		soDegrees m_Yaw;										/*!< Yaw Angle */
		soDegrees m_Pitch;										/*!< Pitch Angle */		
		bool m_IsDirty;											/*!< True if camera change in frame */
		soFrustrum m_Frustum;									/*!< Frustum camera */
		soDegrees m_Fov;										/*!< Field of view */		
		soDegrees m_MaxPitch;									/*!< Max pitch angle */					
		bool m_InvertY;											/*!< If true, the yaw rotation is inverse */
		bool m_LockUp;											/*!< If true, the up direction is lock */
		bool m_EnableUpMovement;								/*!< If true, the up direction movemet is lock */
		uint32 m_ViewportWidth;									/*!< Represent width camera screen */
		uint32 m_ViewportHeight;								/*!< Represent height camera screen */

	public:
		float m_Near;											/*!< Nearest camera point */
		float m_Far;											/*!< Farest camera point */
		SET_AND_GET(soMatrix4x4, PM)				/*!< Projection Matrix */
		SET_AND_GET(soMatrix4x4, VM)					/*!< View Matrix */
		soVector3D m_MaxVelocity;								/*!< Max velocity camera movement */
		soVector3D m_MaxRotationVel;							/*!< Max camera rotation vel */
		soVector3D m_UpDir;										/*!< Up Direction */
		soVector3D m_FrontDir;									/*!< Front Dir */
		soVector3D m_RightDir;									/*!< Right Dir */
		soVector3D m_Position;									/*!< Camera position */
		float m_AspectRatio;									/*!< Aspect Ratio */
		bool m_Orthographic;									/*!< If true, the camera is ortographic */
		soString m_Name;										/*!< Camera name */

		/************************************************************************/
		/* Function										                        */
		/************************************************************************/
	private:
		void SetCameraAxes();									/*!< Update direction vectors */		
		void ShutDown();										/*!< Free class resources */
		void ReBuildProyection();								/*!< Update projection matrix after changes */
		void IsDirty();											/*!< Call it when camera changes in frame */
		
	public:
		RESULT StartUp(const CameraData&_CameraData);			/*!< Class init */		
		void Resize(const uint32& Width, const uint32& Height);	/*!< Update a new aspect ratio */
		void Update(float _DeltaTime);							/*!< Camera update */
		void SetOrthographic(bool _Orthographic);				/*!< Turn on/off ortographic camera */
		void MoveForward(float _Scale = 1.0f);					/*!< Forward camera movement */
		void MoveBackward(float _Scale = 1.0f);					/*!< Back camera movement*/
		void MoveLeft(float _Scale = 1.0f);						/*!< Left camera movement*/
		void MoveRight(float _Scale = 1.0f);					/*!< Right camera movement*/
		void MoveUp(float _Scale = 1.0f);						/*!< Up camera movement*/
		void MoveDown(float _Scale = 1.0f);						/*!< Down camera movement*/
		void Yaw(bool _Positive);								/*!< Yaw Rotation */
		void Pitch(bool _Positive);								/*!< Pitch Rotation */
		void Roll(bool _Positive);								/*!< Roll rotation */
		bool SphereIncideFrustum(const soSphere& _Sphere);		/*!< Check if sphere is inside frustrum */
	};
}

