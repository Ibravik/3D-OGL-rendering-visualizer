/************************************************************************/
/**
* @LC	  4/12/2017
* @file   dtOGLManager.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/8/2017
* @brief  dtOGLManager class definition
* @bug	   No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header files inclution								                */
/************************************************************************/
#include "dtOGLManager.h"

/************************************************************************/
/* dtOGLManager class definition				                        */
/************************************************************************/
namespace DeveloperTest
{
	dtOGLManager::dtOGLManager()
	{		
		// Bind start up function to template
		Connect(std::bind(&dtOGLManager::OnStartUp, this, std::placeholders::_1));

	}
	
	dtOGLManager::~dtOGLManager()
	{
	}

	RESULT dtOGLManager::OnStartUp(const OGLManagerData& _InitInfo)
	{
		printf("Init GL Manager \n");
		// Set init params
		m_WindowPosition = _InitInfo.WindowPosition;
		m_CurrentWindowSize = _InitInfo.WindowSize;

		// Set Position
		glutInitWindowPosition(m_WindowPosition.X, m_WindowPosition.Y);

		// Set Size
		glutInitWindowSize(m_CurrentWindowSize.m_Width, m_CurrentWindowSize.m_Height);

		// Set Active buffer
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

		// Create the new window
		glutCreateWindow("Developer3DTest");

		printf("GL Manager Status: ON \n\n\n");

		return EC_OK;
	}

	void dtOGLManager::OnShutDown()
	{		
	}

	bool dtOGLManager::Resize()
	{
		// Get new size
		m_CurrentWindowSize.m_Width = glutGet(GLUT_WINDOW_WIDTH);
		m_CurrentWindowSize.m_Height = glutGet(GLUT_WINDOW_HEIGHT);

		// Check if it change
		if (m_LastWindowSize != m_CurrentWindowSize)
		{
			m_LastWindowSize = m_CurrentWindowSize;

			// Inform changes
			return true;		
		}

		// Inform no changes
		return false;
	}

	void dtOGLManager::FullScreen(bool& _Switch)
	{
		if (_Switch)
		{
			glutPositionWindow(0, 0);
			glutReshapeWindow(m_WindowedSize.m_Width, m_WindowedSize.m_Height);

			_Switch = false;
		}
		else
		{
			glutFullScreen();
			m_WindowedSize = m_CurrentWindowSize;

			_Switch = true;
		}
	}
}
