/********************************************************************/
/**
* LC	  4/10/2017		
* @file   dtCamera.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2017		
* @brief  dtCamera class definition
* @bug	   No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header inclution files								                */
/************************************************************************/
#include "dtCamera.h"

/************************************************************************/
/* dtCamera	class definition										    */
/************************************************************************/
namespace DeveloperTest
{
	dtCamera::dtCamera()
	{				
		m_AspectRatio = 0.0f;
		m_IsDirty = false;	
		m_Near = 0.0f;
		m_Far = 0.0f;	
		m_Orthographic = false;
		m_InvertY = false;
		m_LockUp = true;
		m_EnableUpMovement = false;
		m_Rotation = soMath::IdentityMatrix3x3();
	}

	dtCamera::~dtCamera()
	{
		ShutDown();
	}

	void dtCamera::IsDirty()
	{
		m_IsDirty = true;
	}

	void dtCamera::SetCameraAxes()
	{
		// Update all the camera directions from rebuild view matrix
		m_RightDir.X = m_VM.m00;
		m_RightDir.Y = m_VM.m10;
		m_RightDir.Z = m_VM.m20;
		if (!m_LockUp)
		{
			m_UpDir.X = m_VM.m01;
			m_UpDir.Y = m_VM.m11;
			m_UpDir.Z = m_VM.m21;
		}
		m_FrontDir.X = m_VM.m02;
		m_FrontDir.Y = m_VM.m12;
		m_FrontDir.Z = m_VM.m22;
	}

	void dtCamera::ReBuildProyection()
	{
		if (m_Orthographic)
		{
			// Build orthographic projection matrix
			{
				float L = 0.0f;
				float R = (float)m_ViewportWidth;
				float B = (float)m_ViewportHeight;
				float T = 0.0f;
				float F = m_Far;
				float N = m_Near;

				m_PM = soMatrix4x4(
					2.0f / (R - L),	0.0f,				0.0f,			0.0f,
					0.0f,			2.0f / (B - T),		0.0f,			0.0f,
					0.0f,			0.0f,				1.0f / (F - N),	0.0f,
					0.0f,			0.0f,				-N / (F - N),	1.0f
				);
			}
		}
		else
		{
			// Build perspective projection matrix
			m_PM = soMath::MatrixPerspectiveForLH(m_Fov, m_AspectRatio, m_Near, m_Far);
		}

		IsDirty();
	}

	void dtCamera::Resize(const uint32& Width, const uint32& Height)
	{
		// Update the aspect ratio from camera screen
		m_AspectRatio = (float)Width / (float)Height;

		// Pojection matrix update
		ReBuildProyection();

		IsDirty();
	}
		
	RESULT dtCamera::StartUp(const CameraData& _CameraInfo)
	{
		// Initialize all the variables in class
		m_MaxPitch = _CameraInfo.MaxPitch;
		m_MaxVelocity = _CameraInfo.MaxVel;
		m_InvertY = _CameraInfo.InvertY;
		m_EnableUpMovement = _CameraInfo.EnableUpMovement;
		m_Position = _CameraInfo.Position;
		m_Fov = _CameraInfo.Fov;
		m_AspectRatio = _CameraInfo.AspectRatio;
		m_Near = _CameraInfo.Near;
		m_Far = _CameraInfo.Far;
		m_UpDir = _CameraInfo.Up;
		m_FrontDir = _CameraInfo.Front;
		m_Velocity = soVector3D(0, 0, 0);
		m_LockUp = _CameraInfo.LockUp;

		m_Name = _CameraInfo.CameraName;

		// Pojection matrix update
		ReBuildProyection();
	
		// Set camera changes
		IsDirty();

		return EC_OK;
	}

	void dtCamera::ShutDown()
	{

	}

	void dtCamera::Update(float _DeltaTime)
	{
		if (m_IsDirty)
		{
			// Camera position update
			m_Position += m_Velocity * _DeltaTime;

			// Camera rotation update
			if (m_Rotation != soMath::IdentityMatrix3x3())
			{
				m_FrontDir = m_FrontDir * (m_Rotation * _DeltaTime);
				soMath::NormalizeVector(m_FrontDir);
			}

			m_Velocity = soVector3D(0.0f, 0.0f, 0.0f);
			m_Rotation = soMath::IdentityMatrix3x3();

			// Camera view point update
			m_LookAt = m_Position + m_FrontDir;

			// View matrix update
			m_VM = soMath::MatrixLookAtLH(m_Position, m_LookAt, m_UpDir);

			// Camera direction axes update
			SetCameraAxes();

			// Frustum update
			m_Frustum.ConstructFrustum(m_PM, m_VM);

			// Camera angles update
			float lookLengthOnXZ = soMath::Sqrt(m_FrontDir.Z * m_FrontDir.Z + m_FrontDir.X * m_FrontDir.X);
			m_Pitch = soRadians(soMath::ArcTan(m_FrontDir.Y / lookLengthOnXZ)).GetDegrees();
			m_Yaw = soRadians(soMath::ArcTan(m_FrontDir.X / m_FrontDir.Z)).GetDegrees();

			// Tag camera changes off
			m_IsDirty = false;
		}		
	}

	void dtCamera::SetOrthographic(bool _Orthographic)
	{
		// Set camera ortographic mode on/off
		m_Orthographic = _Orthographic;

		IsDirty();
	}

	void dtCamera::MoveForward(float _Scale)
	{
		IsDirty();
		if (m_EnableUpMovement)
		{
			m_Velocity += m_FrontDir * (m_MaxVelocity * _Scale);
		}
		else
		{
			soVector3D Move = m_FrontDir * (m_MaxVelocity * _Scale);
			Move.y = 0;
			m_Velocity += Move;
		}
	}

	void dtCamera::MoveBackward(float _Scale)
	{
		IsDirty();
		if (m_EnableUpMovement)
		{
			m_Velocity += -m_FrontDir * (m_MaxVelocity * _Scale);
		}
		else
		{
			soVector3D Move = -m_FrontDir * (m_MaxVelocity * _Scale);
			Move.y = 0;
			m_Velocity += Move;
		}
	}

	void dtCamera::MoveLeft(float _Scale)
	{
		IsDirty();
		m_Velocity += -m_RightDir * (m_MaxVelocity * _Scale);
	}

	void dtCamera::MoveRight(float _Scale)
	{
		IsDirty();
		m_Velocity += m_RightDir * (m_MaxVelocity * _Scale);
	}

	void dtCamera::MoveUp(float _Scale)
	{
		IsDirty();
		if (m_EnableUpMovement)
		{
			m_Velocity += m_UpDir * (m_MaxVelocity * _Scale);
		}
	}

	void dtCamera::MoveDown(float _Scale)
	{
		IsDirty();
		if (m_EnableUpMovement)
		{
			m_Velocity += -m_UpDir * (m_MaxVelocity * _Scale);
		}
	}
		
	void dtCamera::Yaw(bool _Positive)
	{
		IsDirty();

		soDegrees _Angle((_Positive ? m_MaxRotationVel.Y : -m_MaxRotationVel.Y));
		_Angle.Unwind();

		soQuaternion RotationQuaternion(m_UpDir, _Angle);
		soMatrix3x3 Rotation;
		soMath::QuaternionToMatrixRotation3x3(RotationQuaternion, Rotation);
		m_Rotation *= Rotation;
	}

	void dtCamera::Pitch(bool _Positive)
	{
		IsDirty();
		soDegrees _Angle((_Positive ? m_MaxRotationVel.X : -m_MaxRotationVel.X));
		_Angle.Unwind();

		soRadians Radians;
		Radians = (m_InvertY) ? -_Angle.GetRadians() : _Angle.GetRadians();
		m_Pitch -= Radians.GetDegrees();

		if (m_Pitch.GetRadians() > m_MaxPitch.GetRadians())
		{
			Radians += m_Pitch.GetRadians() - m_MaxPitch.GetRadians();
		}
		else if (m_Pitch.GetRadians() < -m_MaxPitch.GetRadians())
		{
			Radians += m_Pitch.GetRadians() + m_MaxPitch.GetRadians();
		}

		soQuaternion RotationQuaternion(m_RightDir, Radians);
		soMatrix3x3 Rotation;
		soMath::QuaternionToMatrixRotation3x3(RotationQuaternion, Rotation);
		m_Rotation *= Rotation;
	}

	void dtCamera::Roll(bool _Positive)
	{
		IsDirty();
		soDegrees _Angle((_Positive ? m_MaxRotationVel.Z : -m_MaxRotationVel.Z));
		_Angle.Unwind();
		
		soQuaternion RotationQuaternion(m_FrontDir, _Angle);
		soMatrix3x3 Rotation;
		soMath::QuaternionToMatrixRotation3x3(RotationQuaternion, Rotation);
		m_Rotation *= Rotation;
	}
	
	bool dtCamera::SphereIncideFrustum(const soSphere & _Sphere)
	{
		return m_Frustum.IsSphereIn(_Sphere);
	}	
}