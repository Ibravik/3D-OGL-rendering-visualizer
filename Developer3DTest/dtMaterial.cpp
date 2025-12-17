/********************************************************************/
/**
* @LC	  4/7/2017
* @file   dtMaterial.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/7/2017
* @brief  dtMaterial class implementation
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Heeader files iclusion								                */
/************************************************************************/
#include "dtOGLManager.h"
#include "dtRenderManager.h"
#include "dtMaterial.h"

/************************************************************************/
/* dtMaterial class definition				                            */
/************************************************************************/
namespace DeveloperTest
{
	dtMaterial::dtMaterial()
	{
	}

	dtMaterial::~dtMaterial()
	{
		ShutDown();
	}

	RESULT dtMaterial::LoadTexture(const MaterialData& _MaterialData, uint8 _MatProp)
	{
		//Build the textures buffer acoording to assimp info			
		aiString aiLoatedString;			//Assimp texture path info		
		soString TexturePath;				//New texture path

		if (_MaterialData.Material && aiReturn::aiReturn_SUCCESS == _MaterialData.Material->GetTexture((aiTextureType)_MatProp, 0, &aiLoatedString))
		{
			TexturePath = _MaterialData.FilePath + GetFileName(soString(s2ws(std::string(aiLoatedString.C_Str()))));

			dtTexture* NewTexture = SOE_NEW dtTexture;

			if (FAIL(NewTexture->StartUp(TexturePath)))
			{
				return EC_FALSE;
			}

			NewTexture->m_TextureTypeID = _MatProp;

			m_TextureArray.push_back(NewTexture);

			return EC_OK;
		}	

		return EC_FALSE;
	}

	RESULT dtMaterial::StartUp(const MaterialData& _MaterialData)
	{
		//Assign material name
		m_MaterialName = _MaterialData.Name;

		//Load material textures and default names
		if (TOHIT(LoadTexture(_MaterialData, aiTextureType_DIFFUSE)))
		{
			m_TextureArray.back()->m_Name = SOE_NEW soString(TEXT("A"));
		}
		if (TOHIT(LoadTexture(_MaterialData, aiTextureType_SPECULAR)))
		{
			m_TextureArray.back()->m_Name = SOE_NEW soString(TEXT("M"));
		}
		if (TOHIT(LoadTexture(_MaterialData, aiTextureType_HEIGHT)))
		{
			m_TextureArray.back()->m_Name = SOE_NEW soString(TEXT("R"));
		}
		if (TOHIT(LoadTexture(_MaterialData, aiTextureType_AMBIENT)))
		{
			m_TextureArray.back()->m_Name = SOE_NEW soString(TEXT("N"));
		}	

		m_TextureArray.push_back(&dtRenderManager::Instance().m_EnvironmentMap);
		m_TextureArray.push_back(&dtRenderManager::Instance().m_IrradianceMap);
		return EC_OK;
	}

	void dtMaterial::ShutDown()
	{
		//Release texture array memory
		while (!m_TextureArray.empty() && *m_TextureArray.back()->m_Name != soString(TEXT("EM")) && *m_TextureArray.back()->m_Name != soString(TEXT("IM")))
		{
			SAFE_DELETE(m_TextureArray.back());
			m_TextureArray.pop_back();
		}
	}

	void dtMaterial::Render(uint32 _ProgramID)
	{
		// Set shader texture buffers 
		for (uint8 i = 0; i != (uint8)m_TextureArray.size(); i++)
		{
			//If the texture load, set to shader
			if (m_TextureArray.at(i)->m_GLHandleID != 0)
			{
				// Bind pass textures (Normal/position)	
				uint32 location;
				location = glGetUniformLocation(_ProgramID, ws2s(*m_TextureArray.at(i)->m_Name).c_str());
				if (location != -1)
				{
					glUniform1i(location, m_TextureArray.at(i)->m_GLHandleID);
					glActiveTexture(GL_TEXTURE0 + m_TextureArray.at(i)->m_GLHandleID);
					glBindTexture(m_TextureArray.at(i)->m_Target, m_TextureArray.at(i)->m_GLHandleID);

					if (m_TextureArray.at(i)->m_SamplerID != 0)
					{
						glBindSampler(m_TextureArray.at(i)->m_GLHandleID, m_TextureArray.at(i)->m_SamplerID);
					}
					else
					{
						glBindSampler(m_TextureArray.at(i)->m_GLHandleID, 0);
					}
				}				
			}
		}
	}

	void dtMaterial::EndRender()
	{
		// Unbind all the texture buffers
		for (uint32 i = 0; i != aiTextureType_UNKNOWN; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glActiveTexture(GL_TEXTURE0);
	}
}