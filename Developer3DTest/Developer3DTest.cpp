/********************************************************************/
/**
* @LC	  4/13/2017
* @file   Developer3DTest.cpp 
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/7/2017
* @brief  OpenGL/Glut 3D Developer test
* @bug	   No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header Files												            */
/************************************************************************/
#include "stdafx.h"
#include <Soul_Math.h>
#include "dtOGLManager.h"
#include "dtRenderManager.h"
#include "dtModel.h"
#include "dtCamera.h"

using namespace DeveloperTest;

/************************************************************************/
/* Global variables                                                     */
/************************************************************************/
std::vector<dtModel*> g_Scene;							/*!< All model scene data */
dtCamera g_MainCamera;									/*!< Main window camera */

/************************************************************************/
/* Window			                                                    */
/************************************************************************/
bool g_FullScreen = false;								/*!< Active full screen */
uint32 g_ScreenShotIndex = 0;							/*!< Current screen shot taken */
bool g_Light = false;									/*!< Camera light */

/************************************************************************/
/* Time variables                                                       */
/************************************************************************/
LARGE_INTEGER Fq;										/*!< Procesor frec */
LARGE_INTEGER g_L0;										/*!< Last read */
LARGE_INTEGER g_L1;										/*!< New Rread*/
float g_DeltaTime = 0.0f;					 			/*!< Deta time betwen frames */
float g_ElapsedTime = 0.0f;								/*!< Time acumulator */

/************************************************************************/
/* Perfomance variables                                                 */
/************************************************************************/
uint32 g_FPSCount = 0;									/*!< FPS amount per sec */
float g_FPS = 0;										/*!< Total FPS amount in one sec */
uint32 g_TotalLoadVertex = 0;							/*!< Total vertex in scene */
uint32 g_TotalMeshAmount = 0;							/*!< Total mesh in scene */
uint32 g_TotalModelAmount = 0;							/*!< Total model in scene */
uint32 g_TotalTriangleAmount = 0;						/*!< Total triangle in scene */

/************************************************************************/
/* Mouse variables                                                      */
/************************************************************************/
int32 g_MouseButton = 0;								/*!< Mouse Buton (left, rigth, middle etc) */
int32 g_MouseState = 0;									/*!< Button state */
int32 g_CurrentMouseX = 0;								/*!< Current Mouse pos X */
int32 g_CurrentMouseY = 0;								/*!< Current Mouse pos Y */
int32 g_LastMouseX = 0;									/*!< Last Mouse pos X */
int32 g_LastMouseY = 0;									/*!< Last Mouse pos Y */

/************************************************************************/
/* Input event				                                            */
/************************************************************************/
enum InputEvent											
{
	IE_RBUTTONDOWN = 0x01,								/*!< Mouse rigth click */
	IE_LBUTTONDOWN = 0x02,								/*!< Mouse left click */
	IE_MBUTTONDOWN = 0x04,								/*!< Mouse midle click */
	IE_KBW = 0x08,										/*!< Keyboard W press */
	IE_KBA = 0x10,										/*!< Keyboard A press */
	IE_KBS = 0x20,										/*!< Keyboard S press */
	IE_KBD = 0x40,										/*!< Keyboard D press */
};
uint64 g_InputEvent = 0;								/*!< BitKey, save all input event in current frame */

/************************************************************************/
/* Camera variables                                                     */
/************************************************************************/
soVector3D g_TranslationSpeed(3, 3, 3);					/*!< Camera Translation speed */
soVector3D g_PanSpeed(10, 10, 10);						/*!< Camera Pan translation speed */
soVector3D g_RotationSpeed(2.5, 2.5, 2.5);				/*!< Camera Rotation speed */

/************************************************************************/
/* Help Functions forward declaration				                    */
/************************************************************************/
void UpdateTime();

void Resize();

void SetCallbackFuctions();

void InitApp(int argc, char **argv);

void FinishApp();

/************************************************************************/
/* Callback functions                                                   */
/************************************************************************/
void KeyBoardDown(unsigned char key, int x, int y)
{
	dtRenderManager* RM = dtRenderManager::InstancePtr();
	(void*)x;
	(void*)y;

	// Clean the past frame instruction	
	g_MainCamera.m_MaxVelocity = g_TranslationSpeed;

	// Check current frame instructions

	// Move forward
	if (key == 'w' || key == 'W')
	{
		g_InputEvent |= IE_KBW;
	}	

	// Move left
	if (key == 'a' || key == 'A')
	{
		g_InputEvent |= IE_KBA;
	}
	
	// Move bacward
	if (key == 's' || key == 'S')
	{
		g_InputEvent |= IE_KBS;
	}
	
	// Move right
	if (key == 'd' || key == 'D')
	{
		g_InputEvent |= IE_KBD;
	}
	
	// esc button to exit
	if (key == 0x1b)
	{
		FinishApp();
		exit(0);
	}

	// Space
	if (key == ' ')
	{
		if (g_Light)
			RM->m_ShaderBuffer.SLC = soVector4D(1, 1, 1, 1);
		else
			RM->m_ShaderBuffer.SLC = soVector4D(0, 0, 0, 1);

		g_Light = !g_Light;
	}

	// Enter
	if (key == 0x0d)
	{
		if (RM->m_ShaderBuffer.CLC == soVector4D(1, 1, 1, 1))
		{
			RM->m_ShaderBuffer.CLC = soVector4D(1, 0, 0, 1);
		}
		else if (RM->m_ShaderBuffer.CLC == soVector4D(1, 0, 0, 1))
		{
			RM->m_ShaderBuffer.CLC = soVector4D(0, 1, 0, 1);
		}
		else if (RM->m_ShaderBuffer.CLC == soVector4D(0, 1, 0, 1))
		{
			RM->m_ShaderBuffer.CLC = soVector4D(0, 0, 1, 1);
		}
		else if (RM->m_ShaderBuffer.CLC == soVector4D(0, 0, 1, 1))
		{
			RM->m_ShaderBuffer.CLC = soVector4D(0, 0, 0, 1);
		}
		else if (RM->m_ShaderBuffer.CLC == soVector4D(0, 0, 0, 1))
		{
			RM->m_ShaderBuffer.CLC = soVector4D(1, 1, 1, 1);
		}		
	}
}

void KeyBoardUp(unsigned char key, int x, int y)
{
	dtRenderManager* RM = dtRenderManager::InstancePtr();
	(void*)x;
	(void*)y;

	// Clean the past frame instruction	
	g_MainCamera.m_MaxVelocity = g_TranslationSpeed;

	// Check current frame instructions

	// Move forward
	if (key == 'w' || key == 'W')
	{
		g_InputEvent &= ~(IE_KBW);
	}

	// Move left
	if (key == 'a' || key == 'A')
	{
		g_InputEvent &= ~(IE_KBA);
	}

	// Move bacward
	if (key == 's' || key == 'S')
	{
		g_InputEvent &= ~(IE_KBS);
	}

	// Move right
	if (key == 'd' || key == 'D')
	{
		g_InputEvent &= ~(IE_KBD);
	}		
}

void UpdateSpecialKeyboardEvent(int key, int x, int y)
{
	(void*)x;
	(void*)y;

	// F1 key controll fullscreen mode
	if (key == GLUT_KEY_F1)
	{
		dtOGLManager::Instance().FullScreen(g_FullScreen);
	}

	// F2 take screen shot
	if (key == GLUT_KEY_F2)
	{
		dtRenderManager::Instance().TakeScreenShot();
	}	
}

void UpdateMouseEvent(int button, int state, int x, int y)
{
	(void*)x;
	(void*)y;

	// Left down
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_InputEvent |= IE_LBUTTONDOWN;
	}

	// Left Up
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		g_InputEvent &= ~(IE_LBUTTONDOWN);
	}

	// Right down
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		g_InputEvent |= IE_RBUTTONDOWN;
	}

	// Right Up
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		g_InputEvent &= ~(IE_RBUTTONDOWN);
	}

	// Mid down
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		g_InputEvent |= IE_MBUTTONDOWN;
	}

	// Mid up
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		g_InputEvent &= ~(IE_MBUTTONDOWN);
	}
}

void UpdateCameraMovement(int x, int y)
{
	// Update current mouse position
	g_LastMouseX = g_CurrentMouseX;
	g_LastMouseY = g_CurrentMouseY;

	g_CurrentMouseX = x;
	g_CurrentMouseY = y;

	// Camera rotation
	g_MainCamera.m_MaxRotationVel = g_RotationSpeed;
	if (!g_MainCamera.m_Orthographic)
	{
		if (g_InputEvent & IE_RBUTTONDOWN)
		{
			if (g_CurrentMouseX < g_LastMouseX)
			{
				g_MainCamera.Yaw(false);
			}
			else if (g_CurrentMouseX > g_LastMouseX)
			{
				g_MainCamera.Yaw(true);
			}

			if (g_CurrentMouseY < g_LastMouseY)
			{
				g_MainCamera.Pitch(false);
			}
			else if (g_CurrentMouseY > g_LastMouseY)
			{
				g_MainCamera.Pitch(true);
			}
		}
	}

	// Pan Movement
	g_MainCamera.m_MaxVelocity = g_PanSpeed;
	if (g_InputEvent & IE_MBUTTONDOWN)
	{
		if (g_CurrentMouseX < g_LastMouseX)
		{
			g_MainCamera.MoveLeft(0.5f);
		}
		else if (g_CurrentMouseX > g_LastMouseX)
		{
			g_MainCamera.MoveRight(0.5f);
		}

		if (g_CurrentMouseY < g_LastMouseY)
		{
			g_MainCamera.MoveUp(0.5f);
		}
		else if (g_CurrentMouseY > g_LastMouseY)
		{
			g_MainCamera.MoveDown(0.5f);
		}
	}	
}

void Update()
{
	dtRenderManager* RM = dtRenderManager::InstancePtr();

	// Take current time
	UpdateTime();

	// Update camera changes
	g_MainCamera.Update(g_DeltaTime);

	// Movement XZ
	g_MainCamera.m_MaxVelocity = g_TranslationSpeed;
	if (g_InputEvent & IE_KBW)
	{
		g_MainCamera.MoveForward();
	}
	if (g_InputEvent & IE_KBA)
	{
		g_MainCamera.MoveLeft();
	}
	if (g_InputEvent & IE_KBS)
	{
		g_MainCamera.MoveBackward();
	}
	if (g_InputEvent & IE_KBD)
	{
		g_MainCamera.MoveRight();
	}

	// Order repaint window
	glutPostRedisplay();

	// Check if there is a resize event
	Resize();

	// Fill shader program parameters		
	RM->m_ShaderBuffer.VM = g_MainCamera.GetVM();
	RM->m_ShaderBuffer.PM = g_MainCamera.GetPM();
	RM->m_ShaderBuffer.VP = g_MainCamera.m_Position;

	RM->m_ShaderBuffer.CLD = g_MainCamera.m_FrontDir;
	RM->m_ShaderBuffer.CLP = g_MainCamera.m_Position;
	
	RM->m_ShaderBuffer.CIC = soDegrees(10).GetRadians();
	RM->m_ShaderBuffer.COC = soDegrees(55).GetRadians();
	RM->m_ShaderBuffer.Near = g_MainCamera.m_Near;
	RM->m_ShaderBuffer.Far = g_MainCamera.m_Far;
	RM->m_ShaderBuffer.Delta += g_DeltaTime * 0.01f;	
}

void Render()
{
	dtRenderManager* RM = dtRenderManager::InstancePtr();
	
	// Render Model list
	RM->Render(g_Scene);

	// Render GUI Info
#ifndef _DEBUG
	// FPS
	RM->WriteTextInScreen(10, 20, TEXT("Developer Test 1.0"), GLUT_BITMAP_9_BY_15);
	RM->WriteTextInScreen(10, 50, float2ws(g_FPS), GLUT_BITMAP_9_BY_15);

	// Total Model in scene
	RM->WriteTextInScreen(10, 90, soString(TEXT("Model")), GLUT_BITMAP_8_BY_13);
	RM->WriteTextInScreen(10, 105, uint2ws(g_TotalModelAmount), GLUT_BITMAP_8_BY_13);

	// Total mesh in scene
	RM->WriteTextInScreen(10, 125, soString(TEXT("Mesh")), GLUT_BITMAP_8_BY_13);
	RM->WriteTextInScreen(10, 140, uint2ws(g_TotalMeshAmount), GLUT_BITMAP_8_BY_13);

	// Total Vertex in scene
	RM->WriteTextInScreen(10, 160, soString(TEXT("Vertex")), GLUT_BITMAP_8_BY_13);
	RM->WriteTextInScreen(10, 175, uint2ws(g_TotalLoadVertex), GLUT_BITMAP_8_BY_13);

	// Total triangle in scene
	RM->WriteTextInScreen(10, 195, soString(TEXT("Triangle")), GLUT_BITMAP_8_BY_13);
	RM->WriteTextInScreen(10, 210, uint2ws(g_TotalTriangleAmount), GLUT_BITMAP_8_BY_13);
#endif
	// Present the back buffer to the screen since rendering is complete.
	glutSwapBuffers();
}

/************************************************************************/
/* Help functions                                                       */
/************************************************************************/
void UpdateTime()
{
	// Take the frec read 
	QueryPerformanceCounter(&g_L1);

	// Obtain delta frec
	long long Diff = g_L1.QuadPart - g_L0.QuadPart;

	// obtain delta time in sec
	g_DeltaTime = (float)Diff / Fq.QuadPart;

	// Update current read
	g_L0 = g_L1;

	// Update render FPS count
	g_FPSCount++;
	g_ElapsedTime += g_DeltaTime;
	if (g_ElapsedTime >= 1.0f)
	{
		g_FPS = (float)g_FPSCount;
		g_FPSCount = 0;
		g_ElapsedTime = 0.0f;
	}
}

void Resize()
{
	// Check if there is an rezice event
	if (dtOGLManager::Instance().Resize())
	{
		// Update camera projection
		g_MainCamera.Resize(dtOGLManager::Instance().m_CurrentWindowSize.m_Width, dtOGLManager::Instance().m_CurrentWindowSize.m_Height);

		// Update render targets
		dtRenderManager::Instance().Resize(dtOGLManager::Instance().m_CurrentWindowSize);
	}
}

void SetCallbackFuctions()
{
	// Set render function
	glutDisplayFunc(Render);

	// Set update function
	glutIdleFunc(Update);

	// Set Mouse function
	glutMotionFunc(UpdateCameraMovement);

	// Set Mouse input function
	glutMouseFunc(UpdateMouseEvent);

	// Set Keyboard function
	glutKeyboardFunc(KeyBoardDown);

	// Set keyboard up func
	glutKeyboardUpFunc(KeyBoardUp);

	// Set keyboard special keys function
	glutSpecialFunc(UpdateSpecialKeyboardEvent);
}

soMatrix4x4 MReflection(soVector4D _P)
{
	soVector3D Normal = _P;
	soMath::NormalizeVector(Normal);
	float W = _P.W;
	_P = Normal;
	_P.w = W;

	return soMatrix4x4(	 1 - (2 * (_P.x * 2)), -2 * (_P.x * _P.y), -2 * (_P.x * _P.z), -2 * (_P.x * _P.W),
												-2 * (_P.x * _P.y), 1 - (2 * (_P.y * 2)), -2 * (_P.y * _P.z), -2 * (_P.y * _P.W),
												-2 * (_P.x * _P.z), -2 * (_P.y * _P.z), 1 - (2 * (_P.z * 2)), -2 * (_P.z * _P.W),
												0, 0, 0, 1);
}

void LoadScenne()
{
	dtModel* Scene;	
	Scene = SOE_NEW dtModel;
	Scene->StartUp(soString(TEXT("Resources\\Model\\Scene\\Scene.fbx")));
	Scene->m_RenderBitKey = RBK_GBuffer | RBK_Shadow;
	g_Scene.push_back(Scene);
	g_TotalLoadVertex += Scene->m_TotalVertex;
	g_TotalMeshAmount += Scene->m_TotalMesh;
	g_TotalModelAmount++;

	Scene = SOE_NEW dtModel;
	Scene->StartUp(soString(TEXT("Resources\\Model\\Scene\\Reflect.fbx")));
	Scene->m_RenderBitKey = RBK_GBuffer | RBK_Reflection;
	Scene->m_RTransform = MReflection(soVector4D(0, -1, 0, -10));
	g_Scene.push_back(Scene);
	g_TotalLoadVertex += Scene->m_TotalVertex;
	g_TotalMeshAmount += Scene->m_TotalMesh;
	g_TotalModelAmount++;
}

void InitApp(int argc, char **argv)
{
	// Glut Init
	glutInit(&argc, argv);
	
	// Start up OGLManager
	OGLManagerData OGLInitData;
	if (FAIL(dtOGLManager::StartUp(OGLInitData)))
	{
		return;
	}

	// Glew Init
	glewInit();

	// Start up dtRenderManager
	if (FAIL(dtRenderManager::StartUp()))
	{
		return;
	}
	dtRenderManager* RM = dtRenderManager::InstancePtr();

	// Camera init
	CameraData CamData;
	CamData.Fov = 60.0f;
	CamData.AspectRatio = (float)OGLInitData.WindowSize.m_Width / (float)OGLInitData.WindowSize.m_Height;
	CamData.Far = 1000.0f;
	CamData.Near = 0.1f;
	CamData.Position = soVector3D(0, 10, 20);
	CamData.Front = soVector3D(0.0f, -0.1f, -1.0f);
	CamData.Up = soVector3D(0.0f, 1.0f, 0.0f);
	CamData.EnableUpMovement = true;
	g_MainCamera.StartUp(CamData);

	RM->m_ShaderBuffer.CLC = soVector4D(1, 1, 1, 1);
		
	RM->m_ShaderBuffer.SLC = soVector4D(1, 1, 1, 1);
		
	// Load scene	
	LoadScenne();

	g_TotalTriangleAmount = g_TotalLoadVertex / 3;

	// Initialize Time Update System
	QueryPerformanceFrequency(&Fq);
	QueryPerformanceCounter(&g_L0);

	// Set Calllback
	SetCallbackFuctions();
}

void FinishApp()
{
	// Free model resources
	while (!g_Scene.empty())
	{
		SAFE_DELETE(g_Scene.back());
		g_Scene.pop_back();
	}

	// ShutDown Managers
	dtRenderManager::Instance().ShutDown();
	dtOGLManager::Instance().ShutDown();
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(int argc, char **argv)
{
	// Generate main window
	InitApp(argc, argv);

	// Glut loop
	glutMainLoop();

	return 0;
}