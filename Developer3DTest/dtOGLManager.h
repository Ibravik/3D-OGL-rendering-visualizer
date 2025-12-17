/************************************************************************/
/**
* @LC	  4/12/2017
* @file   dtOGLManager.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/8/2017
* @brief  dtOGLManager class declaration. This class manage all the GL 
		  functionality.
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header include files						                            */
/************************************************************************/
#include <GL/glew.h>
#include <GL/glut.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <Soul_Math.h>

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* OGLManager init data struct				                            */
	/************************************************************************/
	struct OGLManagerData
	{
		soPoint WindowPosition;				/*!< Initial Windows Position */
		soRect WindowSize;					/*!< Initial Windows Size */

		OGLManagerData()
		{//Assign default params
			WindowSize.m_Width = 1280;
			WindowSize.m_Height = 720;
		}
	};

	/************************************************************************/
	/* dtOGLManager class declaration			                            */
	/************************************************************************/
	class dtOGLManager : public soModule<dtOGLManager, const OGLManagerData&>
	{
	public:
		dtOGLManager();
		~dtOGLManager();

		/************************************************************************/
		/* Variables									                        */
		/************************************************************************/
	private:		
		soRect m_LastWindowSize;									/*!< Last Window size */
		soRect m_WindowedSize;										/*!< Last Window width in window mode */

	public:
		soPoint m_WindowPosition;									/*!< Window position */		
		soRect m_CurrentWindowSize;									/*!< Current Window size */		
		
		/************************************************************************/
		/* Functions									                        */
		/************************************************************************/
	private:
		RESULT OnStartUp(const OGLManagerData& _InitInfo);			/*!< Init manager */
		virtual void OnShutDown()override;							/*!< Free all class resources and shutdown manager */
		
	public:		
		bool Resize();												/*!< Update windows size info */
		void FullScreen(bool& _Switch);								/*!< Set full screen settings */		
	};
}