/************************************************************************/
/**
* @LC	  4/12/2017
* @file   dtRenderManager.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/10/2017
* @brief  dtRenderManager class declaration. This class manage all the 
		  render pipeline.
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header include files						                            */
/************************************************************************/
#include <Soul_Math.h>
#include "dtModel.h"
#include "dtRenderPass.h"

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* Render bit key enum definition                                       */
	/************************************************************************/
	enum RenderBitKey
	{
		RBK_PBR = 0x01,
		RBK_Shadow = 0x02,
		RBK_Reflection = 0x04,
		RBK_GBuffer = 0x08,
	};

	/************************************************************************/
	/* Enum with texture shortcut index                                     */
	/************************************************************************/
	enum TextureIndex
	{
		TI_Albedo,
		TI_NormalRoughness,
		TI_PositionMetallic,
		TI_SSAO,
		TI_Luminance,
		TI_Bright,
		TI_BlurH,
		TI_BlurV,
		TI_AddBright,
		TI_PBRLight,
		TI_Tone,
		TI_Shadows,
		TI_ShadowCoord,
		TI_SkyBox,
		TI_Reflection,
		TI_TOTAL
	};

	/************************************************************************/
	/* dtRenderManager init data struct			                            */
	/************************************************************************/
	class dtRenderManager : public soModule<dtRenderManager>
	{
	public:
		dtRenderManager();
		~dtRenderManager();

		/************************************************************************/
		/* Variables									                        */
		/************************************************************************/
	private:
		uint32 m_ScreenShotIndex;													/*!< Current screen shot taken index */
		dtModel m_ScreenAlignedQuad;												/*!< Screen Aligth Quad model */
		dtModel m_SkyBox;															/*!< SkyBox model */
		uint32 m_PointSampler;														/*!< Point sampler ID */
		uint32 m_LinearSampler;														/*!< Linear sampler ID */
		uint32 m_ComparisonSampler;													/*!< Comparison sampler ID */	
		dtTexture* m_TextureShortCut[TI_TOTAL];										/*!< Render target texture shortcut */
		std::vector<dtModel*>* m_ModelList;											/*!< Local pointer to render model list */
		soString* m_NameBuffer;

		// Shader Pass 
		dtRenderPass m_ShadowPass;													/*!< Shadow pass */
		dtRenderPass m_GBufferPass;													/*!< GBuffer pass */
		dtRenderPass m_PBRPass;														/*!< PBR pass */
		dtRenderPass m_SSAOPass;													/*!< SSAO pass */
		dtRenderPass m_LumPass;														/*!< Lum pass */
		dtRenderPass m_BriPass;														/*!< Bri pass */
		dtRenderPass m_BHPass;														/*!< BH pass */
		dtRenderPass m_BVPass;														/*!< BV pass */
		dtRenderPass m_AddBriPass;													/*!< AB pass */
		dtRenderPass m_TonePass;													/*!< Tone pass */
		dtRenderPass m_SkyBoxPass;													/*!< SkyBox Pass */
		dtRenderPass m_FinalPass;													/*!< Final pass */
		dtRenderPass m_ReflectionPass;												/*!< Reflection pass */

	public:
		dtTexture m_EnvironmentMap;													/*!< Environment cube map */
		dtTexture m_IrradianceMap;													/*!< Irradiance cube map */
		ShaderParameters m_ShaderBuffer;											/*!< Shader program buffer */

		/************************************************************************/
		/* Functions									                        */
		/************************************************************************/
	private:
		RESULT OnStartUp();															/*!< Init manager */
		virtual void OnShutDown()override;											/*!< Free all class resources and shutdown manager */
		RESULT LoadRenderResources();												/*!< Load render resources (models, textures etc) */
		RESULT InitSamplers();														/*!< Initialize point and linear sampler */

		RESULT InitGBufferPass();													/*!< Prepare the GBuffer settings */
		RESULT InitPBRLightPass();													/*!< Prepare the PBR pass setings */
		RESULT InitSSAOPass();														/*!< Prepare the SSAO settings */
		RESULT InitLuminancePass();													/*!< Prepare the Lum settings */
		RESULT InitBrightPass();													/*!< Prepare the Bri settings */
		RESULT InitBlurHPass();														/*!< Prepare the BH settings */
		RESULT InitBlurVPass();														/*!< Prepare the BV settings */
		RESULT InitAddBrightPass();													/*!< Prepare the AB settings */
		RESULT InitTonePass();														/*!< Prepare the AB settings */
		RESULT InitFinalPass();														/*!< Prepare the final settings */		
		RESULT InitShadowSettings();												/*!< Prepare the shadow settings */
		RESULT InitSkyBoxSettings();												/*!< Prepare the Skybox settings */
		RESULT InitReflectionSettings();											/*!< Prepare the reflection settings */
							
		void ApplyGBuffer();														/*!< Render GBuffer output */
		void ApplyPBR();															/*!< Render the pbr textures */
		void ApplySSAO();															/*!< Prepare the output SSAO map */
		void ApplyLuminance();														/*!< Prepare the output Lum map */
		void ApplyBright();															/*!< Prepare the output Bri map */
		void ApplyBlurH(dtTexture* _Texture, soRect _ViewPort);						/*!< Prepare the output BH map */
		void ApplyBlurV(dtTexture* _Texture, soRect _ViewPort);						/*!< Prepare the output BV map */
		void ApplyAddBright(soRect _ViewPort);										/*!< Prepare the output AB map */
		void ApplyTone();															/*!< Prepare the output AB map */
		void ApplyFinal(dtTexture* _Texture);										/*!< Out to back buffer */
		void ApplyShadow();															/*!< Prepare the output shadow map */
		void ApplySkyBox();															/*!< Prepare the output SkyBox map */		
		void ApplyReflection();														/*!< Prepare the output reflection map */		

	public:
		void TakeScreenShot();														/*!< Save assign buffer on texture */
		void WriteTextInScreen(int32 _X, int32 _Y, soString _Text, void* _GlutFont);/*!< Write text in screen in front of all */
		void Resize(const soRect& _BuffSize);										/*!< Reload render targets in windows resize */
		void Render(std::vector<dtModel*>& _ModelList);								/*!< Render all */
	};
}