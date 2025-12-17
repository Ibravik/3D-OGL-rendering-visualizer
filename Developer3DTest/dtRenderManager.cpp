/************************************************************************/
/**
* @LC	  4/12/2017
* @file   dtRenderManager.cpp 
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/10/2017
* @brief  dtRenderManager class definition
* @bug	   No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header files inclution								                */
/************************************************************************/
#include "dtOGLManager.h"
#include "dtRenderManager.h"

/************************************************************************/
/* dtRenderManager class definition				                        */
/************************************************************************/
namespace DeveloperTest
{
	dtRenderManager::dtRenderManager()
	{
		// Bind start up function to template
		Connect(std::bind(&dtRenderManager::OnStartUp, this));

		m_ScreenShotIndex = 0;

		m_NameBuffer = SOE_NEW soString(TEXT("AB"));
	}

	dtRenderManager::~dtRenderManager()
	{
		SAFE_DELETE(m_NameBuffer);
		OnShutDown();
	}

	RESULT dtRenderManager::OnStartUp()
	{
		printf("Init Render Manager \n");

		// Load Resources
		if (FAIL(LoadRenderResources()))
		{
			return EC_FALSE;
		}

		// Init Reflection 
		if (FAIL(InitReflectionSettings()))
		{
			return EC_FALSE;
		}

		// Init GBuffer 
		if (FAIL(InitGBufferPass()))
		{
			return EC_FALSE;
		}

		// Init pbr Setting
		if (FAIL(InitPBRLightPass()))
		{
		return EC_FALSE;
		}

		// Init SSAO 
		if (FAIL(InitSSAOPass()))
		{
		return EC_FALSE;
		}

		// Init Lum 
		if (FAIL(InitLuminancePass()))
		{
			return EC_FALSE;
		}

		// Init Bri 
		if (FAIL(InitBrightPass()))
		{
			return EC_FALSE;
		}

		// Init BH 
		if (FAIL(InitBlurHPass()))
		{
			return EC_FALSE;
		}

		// Init BV 
		if (FAIL(InitBlurVPass()))
		{
			return EC_FALSE;
		}

		// Init AB 
		if (FAIL(InitAddBrightPass()))
		{
			return EC_FALSE;
		}

		// Init Tone 
		if (FAIL(InitTonePass()))
		{
			return EC_FALSE;
		}

		// Init Final 
		if (FAIL(InitFinalPass()))
		{
			return EC_FALSE;
		}
		
		// Init Shadow 
		if (FAIL(InitShadowSettings()))
		{
			return EC_FALSE;
		}

		// Init SkyBox 
		if (FAIL(InitSkyBoxSettings()))
		{
			return EC_FALSE;
		}

		printf("Render Manager Status: ON \n\n\n");
		
		return EC_OK;
	}

	void dtRenderManager::Render(std::vector<dtModel*>& _ModelList)
	{
		soRect CurrentViewPort = dtOGLManager::Instance().m_CurrentWindowSize;

		m_ModelList = &_ModelList;

		// aply reflection
		ApplyReflection();
		m_ShaderBuffer.RM = soMath::IdentityMatrix4x4();

		// Generate the shadow map
		ApplyShadow();

		// Generate GBuffer 
		ApplyGBuffer();

		// Render the light
		ApplyPBR();
		
		// Generate SSAO map
		ApplySSAO();

		// Generate Lum map
		ApplyLuminance();

		// Generate Bri map
		ApplyBright();

		// Generate Blur map
		soRect ViewPort;		

		m_ShaderBuffer.ML = 3;
		ViewPort.m_Width = CurrentViewPort.m_Width >> (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height >> (m_ShaderBuffer.ML);
		soString* Name = m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name;
		m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = m_NameBuffer;
		ApplyBlurH(m_TextureShortCut[TI_Bright], ViewPort);
		ApplyBlurV(m_TextureShortCut[TI_Bright], ViewPort);
		m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = Name;
		ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
		ApplyAddBright(ViewPort);
		
		m_ShaderBuffer.ML--;//2
		ViewPort.m_Width = CurrentViewPort.m_Width >> (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height >> (m_ShaderBuffer.ML);
		ApplyBlurH(m_TextureShortCut[TI_AddBright], ViewPort);
		ApplyBlurV(m_TextureShortCut[TI_AddBright], ViewPort);				
		ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
		ApplyAddBright(ViewPort);

		m_ShaderBuffer.ML--;//1
		ViewPort.m_Width = CurrentViewPort.m_Width >> (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height >> (m_ShaderBuffer.ML);
		ApplyBlurH(m_TextureShortCut[TI_AddBright], ViewPort);
		ApplyBlurV(m_TextureShortCut[TI_AddBright], ViewPort);
		ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
		ApplyAddBright(ViewPort);

		m_ShaderBuffer.ML--;//0
		ApplyBlurH(m_TextureShortCut[TI_AddBright], CurrentViewPort);
		ApplyBlurV(m_TextureShortCut[TI_AddBright], CurrentViewPort);
		ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
		ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
		ApplyAddBright(ViewPort);
				
		// apply SkyBox
		ApplySkyBox();
		
		// apply tone maping
		ApplyTone();
				
		// apply Final to back buffer
		ApplyFinal(m_TextureShortCut[TI_Tone]);		
	}

	void dtRenderManager::OnShutDown()
	{
		m_SkyBox.m_MeshList.front()->m_Material.m_TextureArray.clear();
		m_ScreenAlignedQuad.m_MeshList.front()->m_Material.m_TextureArray.clear();
	}

	void dtRenderManager::TakeScreenShot()
	{
		// Take current buffer size
		uint32 Width = dtOGLManager::Instance().m_CurrentWindowSize.m_Width;
		uint32 Height = dtOGLManager::Instance().m_CurrentWindowSize.m_Height;

		// Create the new ScreenShot Name 
		soString Name = TEXT("ScreenShot") + uint2ws(m_ScreenShotIndex) + TEXT(".bmp");

		SOIL_save_screenshot(ws2s(Name).c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, Width, Height);

		m_ScreenShotIndex++;
	}

	void dtRenderManager::WriteTextInScreen(int32 _X, int32 _Y, soString _Text, void* _GlutFont)
	{
		// Take current buffer size
		int32 Width = dtOGLManager::Instance().m_CurrentWindowSize.m_Width;
		int32 Height = dtOGLManager::Instance().m_CurrentWindowSize.m_Height;

		// Default shader program
		glUseProgram(0);

		// Set text color
		glColor4d(0.0, 1.0, 0.0, 1.0f);

		// Set ortographic projection
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, (double)Width, 0, (double)Height);
		glScalef(1, -1, 1);
		glTranslatef(0, -(float)Height, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		//Render text
		std::string Test = ws2s(_Text);
		const char* msg = Test.c_str();
		glRasterPos2f(_X, _Y);
		while (*msg)
		{
			glutBitmapCharacter(_GlutFont, *msg);
			msg++;
		}

		// Reset perspective projection
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();	
	}

	void dtRenderManager::Resize(const soRect& _BuffSize)
	{
		m_GBufferPass.Resize(_BuffSize);
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("AL"));
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(1)->m_Name = SOE_NEW soString(TEXT("NR"));
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(2)->m_Name = SOE_NEW soString(TEXT("PM"));
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(3)->m_Name = SOE_NEW soString(TEXT("SC"));
		m_TextureShortCut[TI_Albedo] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(0);
		m_TextureShortCut[TI_NormalRoughness] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(1);
		m_TextureShortCut[TI_PositionMetallic] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(2);
		m_TextureShortCut[TI_ShadowCoord] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(3);

		m_ShadowPass.Resize(_BuffSize);
		m_ShadowPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("S"));
		m_TextureShortCut[TI_Shadows] = m_ShadowPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_SkyBoxPass.Resize(_BuffSize);
		m_SkyBoxPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("SB"));
		m_TextureShortCut[TI_SkyBox] = m_SkyBoxPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_FinalPass.Resize(_BuffSize);

		m_SSAOPass.Resize(_BuffSize);
		m_SSAOPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("SSAO"));
		m_TextureShortCut[TI_SSAO] = m_SSAOPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_LumPass.Resize(_BuffSize);
		m_LumPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("Lum"));
		m_TextureShortCut[TI_Luminance] = m_LumPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_BriPass.Resize(_BuffSize);
		m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("Bri"));
		m_TextureShortCut[TI_Bright] = m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_BHPass.Resize(_BuffSize);
		m_BHPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("BH"));
		m_TextureShortCut[TI_BlurH] = m_BHPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_BVPass.Resize(_BuffSize);
		m_BVPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("BV"));
		m_TextureShortCut[TI_BlurV] = m_BVPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_AddBriPass.Resize(_BuffSize);
		m_AddBriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("AB"));
		m_TextureShortCut[TI_AddBright] = m_AddBriPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_TonePass.Resize(_BuffSize);
		m_TonePass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("T"));
		m_TextureShortCut[TI_Tone] = m_TonePass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		m_PBRPass.Resize(_BuffSize);
		m_PBRPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("PBR"));
		m_TextureShortCut[TI_PBRLight] = m_PBRPass.m_FrameBuffer.m_RenderTargetTexture.at(0);
	}
	
	RESULT dtRenderManager::LoadRenderResources()
	{	
		//Load irradiance and environment map
		std::vector<soString> FilePath;
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds-0.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds-1.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds-2.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds-3.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds-4.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds-5.tga")));
		if (FAIL(m_EnvironmentMap.StartUp(FilePath)))
		{
			return EC_FALSE;
		}
		m_EnvironmentMap.m_Name = SOE_NEW soString(TEXT("EM"));

		FilePath.clear();
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds_Diffuse-0.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds_Diffuse-1.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds_Diffuse-2.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds_Diffuse-3.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds_Diffuse-4.tga")));
		FilePath.push_back(soString(TEXT("Resources\\Default\\Clouds_Diffuse-5.tga")));
		if (FAIL(m_IrradianceMap.StartUp(FilePath)))
		{
			return EC_FALSE;
		}
		m_IrradianceMap.m_Name = SOE_NEW soString(TEXT("IM"));
		
		// Load Skybox mesh
		if (FAIL(m_SkyBox.StartUp(soString(TEXT("Resources\\Model\\SkyboxMesh.obj")))))
		{
			return EC_FALSE;
		}
		m_SkyBox.m_MeshList.front()->m_Material.m_TextureArray.push_back(&m_EnvironmentMap);

		// Load screen align quad mesh
		if (FAIL(m_ScreenAlignedQuad.StartUp(soString(TEXT("Resources\\Model\\SAQ.obj")))))
		{
			return EC_FALSE;
		}
		
		InitSamplers();
				
		return EC_OK;
	}

	RESULT dtRenderManager::InitSamplers()
	{
		glGenSamplers(1, &m_PointSampler);
		glSamplerParameteri(m_PointSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glSamplerParameteri(m_PointSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glSamplerParameteri(m_PointSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(m_PointSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glGenSamplers(1, &m_LinearSampler);
		glSamplerParameteri(m_LinearSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(m_LinearSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameteri(m_LinearSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(m_LinearSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glGenSamplers(1, &m_ComparisonSampler);
		glSamplerParameteri(m_ComparisonSampler, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glSamplerParameteri(m_ComparisonSampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		glSamplerParameteri(m_ComparisonSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glSamplerParameteri(m_ComparisonSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(m_ComparisonSampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glSamplerParameteri(m_ComparisonSampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		return EC_OK;
	}

	RESULT dtRenderManager::InitGBufferPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_GBufferPass.m_FrameBuffer.m_ColorOn = true;
		m_GBufferPass.m_FrameBuffer.m_FrameBufferOn = true;

		// GBuffer		
		RPData.FSpath = TEXT("Resources\\Shaders\\GBufferPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\GBufferVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 4;
		RPData.RenderTargetDataInit.DepBuffer = true;
		RPData.RenderTargetDataInit.StencilBuffer = true;

		if (FAIL(m_GBufferPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init GBuffer settings failed in GBuffer pass");
			return EC_FALSE;
		}
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("AL"));
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(1)->m_Name = SOE_NEW soString(TEXT("NR"));
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(2)->m_Name = SOE_NEW soString(TEXT("PM"));
		m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(3)->m_Name = SOE_NEW soString(TEXT("SC"));

		m_TextureShortCut[TI_Albedo] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(0);
		m_TextureShortCut[TI_NormalRoughness] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(1);
		m_TextureShortCut[TI_PositionMetallic] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(2);
		m_TextureShortCut[TI_ShadowCoord] = m_GBufferPass.m_FrameBuffer.m_RenderTargetTexture.at(3);

		return EC_OK;
	}

	RESULT dtRenderManager::InitShadowSettings()
	{
		RenderPassData RPData;

		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = soRect(0,0,1024,1024);
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_DEPTH_COMPONENT16;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_DEPTH_COMPONENT;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_ComparisonSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_DEPTH_ATTACHMENT;
		m_ShadowPass.m_FrameBuffer.m_ColorOn = true;
		m_ShadowPass.m_FrameBuffer.m_FrameBufferOn = true;

		// Shadow		
		RPData.FSpath = TEXT("Resources\\Shaders\\ShadowPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ShadowVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_ShadowPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init Shadow settings failed in GBuffer pass");
			return EC_FALSE;
		}
		
		m_ShadowPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("S"));		
		m_TextureShortCut[TI_Shadows] = m_ShadowPass.m_FrameBuffer.m_RenderTargetTexture.at(0); 

		return EC_OK;
	}

	RESULT dtRenderManager::InitSkyBoxSettings()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_SkyBoxPass.m_FrameBuffer.m_ColorOn = true;
		m_SkyBoxPass.m_FrameBuffer.m_FrameBufferOn = true;

		// SkyBox		
		RPData.FSpath = TEXT("Resources\\Shaders\\SkyBoxPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\SkyBoxVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = true;
		RPData.RenderTargetDataInit.StencilBuffer = true;
		RPData.RenderTargetDataInit.DeeptID = m_GBufferPass.m_FrameBuffer.m_DepthBuffer.m_GLHandleID;

		if (FAIL(m_SkyBoxPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init Shadow settings failed in GBuffer pass");
			return EC_FALSE;
		}

		m_SkyBoxPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("SB"));
		m_TextureShortCut[TI_SkyBox] = m_SkyBoxPass.m_FrameBuffer.m_RenderTargetTexture.at(0);
		
		return EC_OK;
	}

	RESULT dtRenderManager::InitReflectionSettings()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_ReflectionPass.m_FrameBuffer.m_ColorOn = true;
		m_ReflectionPass.m_FrameBuffer.m_FrameBufferOn = true;

		// GBuffer		
		RPData.FSpath = TEXT("Resources\\Shaders\\ReflectionPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_ReflectionPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init GBuffer settings failed in GBuffer pass");
			return EC_FALSE;
		}
		m_ReflectionPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("RT"));

		m_TextureShortCut[TI_Reflection] = m_ReflectionPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitFinalPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		m_FinalPass.m_FrameBuffer.m_ColorOn = false;
		m_FinalPass.m_FrameBuffer.m_FrameBufferOn = false;

		// Final pass		
		RPData.FSpath = TEXT("Resources\\Shaders\\FinalPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 0;		
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_FinalPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init Shadow settings failed in GBuffer pass");
			return EC_FALSE;
		}

		return EC_OK;
	}

	RESULT dtRenderManager::InitSSAOPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_SSAOPass.m_FrameBuffer.m_ColorOn = true;
		m_SSAOPass.m_FrameBuffer.m_FrameBufferOn = true;

		// GBuffer		
		RPData.FSpath = TEXT("Resources\\Shaders\\SSAOPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_SSAOPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init SSAO settings failed in GBuffer pass");
			return EC_FALSE;
		}

		m_SSAOPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("SSAO"));
		m_TextureShortCut[TI_SSAO] = m_SSAOPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitLuminancePass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_LumPass.m_FrameBuffer.m_ColorOn = true;
		m_LumPass.m_FrameBuffer.m_FrameBufferOn = true;

		// GBuffer		
		RPData.FSpath = TEXT("Resources\\Shaders\\LuminancePS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_LumPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init SSAO settings failed in GBuffer pass");
			return EC_FALSE;
		}

		m_LumPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("Lum"));
		m_TextureShortCut[TI_Luminance] = m_LumPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitBrightPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_PointSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_BriPass.m_FrameBuffer.m_ColorOn = true;
		m_BriPass.m_FrameBuffer.m_FrameBufferOn = true;

		// Bri		
		RPData.FSpath = TEXT("Resources\\Shaders\\BrightPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_BriPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init Bri settings failed in Bri pass");
			return EC_FALSE;
		}

		m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("Bri"));
		m_TextureShortCut[TI_Bright] = m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitBlurHPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;
		BufferSize.m_Width /= 2.0f;
		BufferSize.m_Height /= 2.0f;
	
		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_PointSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_BHPass.m_FrameBuffer.m_ColorOn = true;
		m_BHPass.m_FrameBuffer.m_FrameBufferOn = true;

		// Bri		
		RPData.FSpath = TEXT("Resources\\Shaders\\BlurHPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_BHPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init BH settings failed in BH pass");
			return EC_FALSE;
		}

		m_BHPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("BH"));
		m_TextureShortCut[TI_BlurH] = m_BHPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitBlurVPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;
		BufferSize.m_Width /= 2.0f;
		BufferSize.m_Height /= 2.0f;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_PointSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_BVPass.m_FrameBuffer.m_ColorOn = true;
		m_BVPass.m_FrameBuffer.m_FrameBufferOn = true;

		// Bri		
		RPData.FSpath = TEXT("Resources\\Shaders\\BlurVPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_BVPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init BH settings failed in BH pass");
			return EC_FALSE;
		}

		m_BVPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("BV"));
		m_TextureShortCut[TI_BlurV] = m_BVPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitAddBrightPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_PointSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_AddBriPass.m_FrameBuffer.m_ColorOn = true;
		m_AddBriPass.m_FrameBuffer.m_FrameBufferOn = true;

		// Bri		
		RPData.FSpath = TEXT("Resources\\Shaders\\AddBrightPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_AddBriPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init AB settings failed in AB pass");
			return EC_FALSE;
		}

		m_AddBriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("AB"));
		m_TextureShortCut[TI_AddBright] = m_AddBriPass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitTonePass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_TonePass.m_FrameBuffer.m_ColorOn = true;
		m_TonePass.m_FrameBuffer.m_FrameBufferOn = true;

		// Light PBR		
		RPData.FSpath = TEXT("Resources\\Shaders\\TonePS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = false;
		RPData.RenderTargetDataInit.StencilBuffer = false;

		if (FAIL(m_TonePass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init pbr settings failed in GBuffer pass");
			return EC_FALSE;
		}

		m_TonePass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("T"));
		m_TextureShortCut[TI_Tone] = m_TonePass.m_FrameBuffer.m_RenderTargetTexture.at(0);

		return EC_OK;
	}

	RESULT dtRenderManager::InitPBRLightPass()
	{
		soRect BufferSize = dtOGLManager::Instance().m_CurrentWindowSize;

		RenderPassData RPData;
		RPData.RenderTargetDataInit.TextureDataInit.BufferSize = BufferSize;
		RPData.RenderTargetDataInit.TextureDataInit.InternalFormat = GL_RGBA16F;
		RPData.RenderTargetDataInit.TextureDataInit.Format = GL_RGBA;
		RPData.RenderTargetDataInit.TextureDataInit.SamplerID = m_LinearSampler;
		RPData.RenderTargetDataInit.TextureDataInit.Type = GL_FLOAT;
		RPData.RenderTargetDataInit.TextureDataInit.AtachmentType = GL_COLOR_ATTACHMENT0_EXT;
		m_PBRPass.m_FrameBuffer.m_ColorOn = true;
		m_PBRPass.m_FrameBuffer.m_FrameBufferOn = true;

		// Light PBR		
		RPData.FSpath = TEXT("Resources\\Shaders\\PBRLightPS.glsl");
		RPData.VSpath = TEXT("Resources\\Shaders\\ScreenAlignedQuadVS.glsl");
		RPData.RenderTargetDataInit.BufferNumber = 1;
		RPData.RenderTargetDataInit.DepBuffer = true;
		RPData.RenderTargetDataInit.StencilBuffer = false;
		RPData.RenderTargetDataInit.DeeptID = m_GBufferPass.m_FrameBuffer.m_DepthBuffer.m_GLHandleID;
		
		if(FAIL(m_PBRPass.StartUp(RPData)))
		{
			SOE_OutputLOG("dtRenderManager", "InitPBRSettings", "Init pbr settings failed in GBuffer pass");
			return EC_FALSE;
		}	

		m_PBRPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = SOE_NEW soString(TEXT("PBR"));
		m_TextureShortCut[TI_PBRLight] = m_PBRPass.m_FrameBuffer.m_RenderTargetTexture.at(0);
				
		return EC_OK;
	}
	
	void dtRenderManager::ApplyGBuffer()
	{
		/************************************************************************/
		/* GBuffer Pass                                                         */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_GBufferPass.BindPass(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		m_GBufferPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClearDepth(1.0f);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glClearStencil(0.0f);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		// Render model list
		for (size_t i = 0; i < m_ModelList->size(); i++)
		{
			if (m_ModelList->at(i)->m_RenderBitKey & RBK_GBuffer)
			{
				if (m_ModelList->at(i)->m_RenderBitKey & RBK_Reflection)
				{
					uint32 location;
					location = glGetUniformLocation(m_GBufferPass.m_ShaderProgram.m_GLHandleID, "RT");
					if (location != -1)
					{
						glUniform1i(location, m_TextureShortCut[TI_Reflection]->m_GLHandleID);
						glActiveTexture(GL_TEXTURE0 + m_TextureShortCut[TI_Reflection]->m_GLHandleID);
						glBindTexture(GL_TEXTURE_2D, m_TextureShortCut[TI_Reflection]->m_GLHandleID);
					}
				}
				m_ModelList->at(i)->Render(m_GBufferPass.m_ShaderProgram.m_GLHandleID);
			}
		}

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_Albedo]->m_GLHandleID);
		glGenerateTextureMipmap(m_TextureShortCut[TI_NormalRoughness]->m_GLHandleID);
		glGenerateTextureMipmap(m_TextureShortCut[TI_PositionMetallic]->m_GLHandleID);
		glGenerateTextureMipmap(m_TextureShortCut[TI_ShadowCoord]->m_GLHandleID);

		// Unbind pass settings
		m_GBufferPass.UnBindPass();
	}

	void dtRenderManager::ApplyShadow()
	{
		/************************************************************************/
		/* Shadow Pass                                                          */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_ShadowPass.BindPass(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_ShadowPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClearDepth(1.0f);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		// Render model list
		for (size_t i = 0; i < m_ModelList->size(); i++)
		{
			if (m_ModelList->at(i)->m_RenderBitKey & RBK_Shadow)
			{
				m_ModelList->at(i)->Render(m_ShadowPass.m_ShaderProgram.m_GLHandleID);
			}
		}

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_Shadows]->m_GLHandleID);

		// Unbind pass settings
		m_ShadowPass.UnBindPass();
	}

	void dtRenderManager::ApplySkyBox()
	{
		/************************************************************************/
		/* SkyBox Pass                                                          */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_SkyBoxPass.BindPass(GL_COLOR_BUFFER_BIT);
		m_SkyBoxPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glDisable(GL_CULL_FACE);

		// Create world matrix
		float Scale = (m_ShaderBuffer.Far - m_ShaderBuffer.Near);
		Scale -= Scale*0.05f;
		m_SkyBox.m_Transform = soMath::TransposeMatrix(soMath::RotationMatrix4x4(-m_ShaderBuffer.Delta, Y_Axis) * soMath::TranslationMatrix4x4(m_ShaderBuffer.VP) * soMath::ScalarMatrix4x4(soVector3D(Scale, Scale, Scale)));
		m_ShaderBuffer.SkyBoxTransform = soMath::RotationMatrix4x4(-m_ShaderBuffer.Delta, Y_Axis);

		// Render model list
		m_SkyBox.Render(m_SkyBoxPass.m_ShaderProgram.m_GLHandleID);

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_Tone]->m_GLHandleID);

		// Unbind pass settings
		m_SkyBoxPass.UnBindPass();
	}

	void dtRenderManager::ApplyReflection()
	{
		soRect CurrentViewPort = dtOGLManager::Instance().m_CurrentWindowSize;

		/************************************************************************/
		/* Reflection Pass                                                      */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_ReflectionPass.BindPass(GL_COLOR_BUFFER_BIT);

		// Render model list
		for (size_t i = 0; i < m_ModelList->size(); i++)
		{
			if (m_ModelList->at(i)->m_RenderBitKey & RBK_Reflection)
			{
				m_ShaderBuffer.RM = soMath::TransposeMatrix(m_ModelList->at(i)->m_RTransform);

				// Generate the shadow map
				ApplyShadow();

				// Generate GBuffer 
				ApplyGBuffer();

				// Render the light
				ApplyPBR();

				// Generate SSAO map
				ApplySSAO();

				// Generate Lum map
				ApplyLuminance();

				// Generate Bri map
				ApplyBright();

				// Generate Blur map
				soRect ViewPort;

				m_ShaderBuffer.ML = 3;
				ViewPort.m_Width = CurrentViewPort.m_Width >> (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height >> (m_ShaderBuffer.ML);
				soString* Name = m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name;
				m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = m_NameBuffer;
				ApplyBlurH(m_TextureShortCut[TI_Bright], ViewPort);
				ApplyBlurV(m_TextureShortCut[TI_Bright], ViewPort);
				m_BriPass.m_FrameBuffer.m_RenderTargetTexture.at(0)->m_Name = Name;
				ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
				ApplyAddBright(ViewPort);

				m_ShaderBuffer.ML--;//2
				ViewPort.m_Width = CurrentViewPort.m_Width >> (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height >> (m_ShaderBuffer.ML);
				ApplyBlurH(m_TextureShortCut[TI_AddBright], ViewPort);
				ApplyBlurV(m_TextureShortCut[TI_AddBright], ViewPort);
				ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
				ApplyAddBright(ViewPort);

				m_ShaderBuffer.ML--;//1
				ViewPort.m_Width = CurrentViewPort.m_Width >> (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height >> (m_ShaderBuffer.ML);
				ApplyBlurH(m_TextureShortCut[TI_AddBright], ViewPort);
				ApplyBlurV(m_TextureShortCut[TI_AddBright], ViewPort);
				ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
				ApplyAddBright(ViewPort);

				m_ShaderBuffer.ML--;//0
				ApplyBlurH(m_TextureShortCut[TI_AddBright], CurrentViewPort);
				ApplyBlurV(m_TextureShortCut[TI_AddBright], CurrentViewPort);
				ViewPort.m_Width = CurrentViewPort.m_Width << (m_ShaderBuffer.ML);
				ViewPort.m_Height = CurrentViewPort.m_Height << (m_ShaderBuffer.ML);
				ApplyAddBright(ViewPort);

				// apply SkyBox
				ApplySkyBox();

				// apply tone maping
				ApplyTone();

				/************************************************************************/
				/* Reflection Pass                                                      */
				/************************************************************************/
				//Set shader and framebuffer
				m_ReflectionPass.BindPass(GL_COLOR_BUFFER_BIT);

				// General settings change
				glDisable(GL_CULL_FACE);
							
				// Render model list
				m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_Reflection]);
				m_ScreenAlignedQuad.Render(m_ReflectionPass.m_ShaderProgram.m_GLHandleID);

				m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();
				
				//Generate mips 
				glGenerateTextureMipmap(m_TextureShortCut[TI_Reflection]->m_GLHandleID);

				// Unbind pass settings
				m_ReflectionPass.UnBindPass();
			}
		}
	}

	void dtRenderManager::ApplyFinal(dtTexture* _Texture)
	{
		/************************************************************************/
		/* Final Pass					                                        */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_FinalPass.BindPass(GL_COLOR_BUFFER_BIT);

		// General settings change
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);		

		// Render model list	
		uint32 location;
		location = glGetUniformLocation(m_FinalPass.m_ShaderProgram.m_GLHandleID, "F");
		if (location != -1)
		{
			glUniform1i(location, _Texture->m_GLHandleID);
			glActiveTexture(GL_TEXTURE0 + _Texture->m_GLHandleID);
			glBindTexture(GL_TEXTURE_2D, _Texture->m_GLHandleID);
		}
		m_ScreenAlignedQuad.Render(m_FinalPass.m_ShaderProgram.m_GLHandleID);

		// Unbind pass settings
		m_FinalPass.UnBindPass();
	}

	void dtRenderManager::ApplySSAO()
	{
		/************************************************************************/
		/* SSAO	Pass						                                    */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		//Set shader and framebuffer
		m_SSAOPass.BindPass(GL_COLOR_BUFFER_BIT);

		// General settings change
		glDisable(GL_CULL_FACE);

		// Render model
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_NormalRoughness]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_PositionMetallic]);
		m_ScreenAlignedQuad.Render(m_SSAOPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_SSAO]->m_GLHandleID);

		// Unbind pass settings
		m_SSAOPass.UnBindPass();
	}

	void dtRenderManager::ApplyLuminance()
	{
		/************************************************************************/
		/* Lum Pass					                                    */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_LumPass.BindPass(GL_COLOR_BUFFER_BIT);

		// General settings change
		glDisable(GL_CULL_FACE);

		//Render model
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_PBRLight]);
		m_ScreenAlignedQuad.Render(m_LumPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_Luminance]->m_GLHandleID);

		// Unbind pass settings
		m_LumPass.UnBindPass();
	}

	void dtRenderManager::ApplyBright()
	{
		/************************************************************************/
		/* Bri Pass						                                    */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_BriPass.BindPass(GL_COLOR_BUFFER_BIT);

		// General settings change
		glDisable(GL_CULL_FACE);

		//Render model
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_Luminance]);
		m_ScreenAlignedQuad.Render(m_BriPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_Bright]->m_GLHandleID);

		// Unbind pass settings
		m_BriPass.UnBindPass();
	}

	void dtRenderManager::ApplyBlurH(dtTexture* _Texture, soRect _ViewPort)
	{
		/************************************************************************/
		/* BH Pass						                                    */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_BHPass.BindPass(GL_COLOR_BUFFER_BIT, &_ViewPort);
		m_BHPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glDisable(GL_CULL_FACE);

		// Render model 
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(_Texture);
		m_ScreenAlignedQuad.Render(m_BHPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_BlurH]->m_GLHandleID);

		// Unbind pass settings
		m_BHPass.UnBindPass();
	}

	void dtRenderManager::ApplyBlurV(dtTexture* _Texture, soRect _ViewPort)
	{
		/************************************************************************/
		/* BV Pass															    */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_BVPass.BindPass(GL_COLOR_BUFFER_BIT, &_ViewPort);
		m_BVPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glDisable(GL_CULL_FACE);

		//Render model
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(_Texture);
		m_ScreenAlignedQuad.Render(m_BVPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_BlurV]->m_GLHandleID);

		// Unbind pass settings
		m_BVPass.UnBindPass();
	}

	void dtRenderManager::ApplyAddBright(soRect _ViewPort)
	{
		/************************************************************************/
		/* AB Pass																*/
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_AddBriPass.BindPass(GL_COLOR_BUFFER_BIT, &_ViewPort);
		m_AddBriPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glDisable(GL_CULL_FACE);

		//Render pass
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_Bright]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_BlurH]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_BlurV]);
		m_ScreenAlignedQuad.Render(m_AddBriPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_AddBright]->m_GLHandleID);

		// Unbind pass settings
		m_AddBriPass.UnBindPass();
	}

	void dtRenderManager::ApplyTone()
	{
		/************************************************************************/
		/* Tone Pass						                                    */
		/************************************************************************/
		//Set shader and framebuffer
		m_TonePass.BindPass(0x00);
		m_TonePass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_CULL_FACE);

		//Render model
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_PBRLight]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_SSAO]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_AddBright]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_SkyBox]);
		m_ScreenAlignedQuad.Render(m_TonePass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_Tone]->m_GLHandleID);

		// Unbind pass settings
		m_TonePass.UnBindPass();
	}

	void dtRenderManager::ApplyPBR()
	{	
		/************************************************************************/
		/* PBR Pass										                        */
		/************************************************************************/
		// Bind pass settings and shader buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set shader and framebuffer
		m_PBRPass.BindPass(GL_COLOR_BUFFER_BIT);
		m_PBRPass.m_ShaderProgram.SetShaderParameters(m_ShaderBuffer);

		// General settings change
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_Albedo]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_NormalRoughness]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_PositionMetallic]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_Shadows]);
		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.push_back(m_TextureShortCut[TI_ShadowCoord]);
		m_ScreenAlignedQuad.Render(m_PBRPass.m_ShaderProgram.m_GLHandleID);

		m_ScreenAlignedQuad.m_MeshList.at(0)->m_Material.m_TextureArray.clear();

		//Generate mips 
		glGenerateTextureMipmap(m_TextureShortCut[TI_PBRLight]->m_GLHandleID);

		// Unbind pass settings
		m_PBRPass.UnBindPass();
				
	}
}