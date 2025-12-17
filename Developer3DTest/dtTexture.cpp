/********************************************************************/
/**
* @LC     4/7/2017
* @file   dtTexture.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  dtTexture class implementation
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <GL/glew.h>
#include <SOIL.h>
#include "dtTexture.h"
 
/************************************************************************/
/* dtTexture declaration											    */
/************************************************************************/
namespace DeveloperTest
{
	dtTexture::dtTexture()
	{
		m_TextureData = nullptr;
		m_Width = 0;
		m_Height = 0;
		m_GLHandleID = 0;
		m_TextureTypeID = 0;
		m_SamplerID = 0;
	}

	dtTexture::~dtTexture()
	{
		ShutDown();

		SAFE_DELETE(m_Name);
	}

	RESULT dtTexture::StartUp(const soString& _FilePath)
	{
		printf("Load %s File Path \n", ws2s(_FilePath).c_str());
		//Load texture data
		if (FAIL(Load(_FilePath)))
		{
			return EC_FALSE;
		}
		
		// Generate an ID for the texture.
		glGenTextures(1, &m_GLHandleID);

		// Bind the texture as a 2D texture.
		glBindTexture(GL_TEXTURE_2D, m_GLHandleID);

		// Load the image data into the texture unit.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);

		// Set the texture color clamp to the edge.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// Set the texture filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Generate mipmaps for the texture.
		glGenerateMipmap(GL_TEXTURE_2D);

		// Release software data
		SOIL_free_image_data(m_TextureData);

		m_Target = GL_TEXTURE_2D;

		//Unbind texture buffer
		glBindTexture(GL_TEXTURE_2D, 0);

		printf("%s Correct \n", ws2s(_FilePath).c_str());
		return EC_OK;
	}

	RESULT dtTexture::StartUp(const TextureData& _TextureData)
	{
		// The texture we're going to render to
		glGenTextures(1, &m_GLHandleID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, m_GLHandleID);

		// Give an empty image to OpenGL ( the last "0" )
		glTexImage2D(GL_TEXTURE_2D, 0, _TextureData.InternalFormat, _TextureData.BufferSize.m_Width, _TextureData.BufferSize.m_Height, 0, _TextureData.Format, _TextureData.Type, 0);
		m_Width = _TextureData.BufferSize.m_Width;
		m_Height = _TextureData.BufferSize.m_Height;

		m_SamplerID = _TextureData.SamplerID;

		m_Target = GL_TEXTURE_2D;
				
		// automatic mipmap
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 

		return EC_OK;
	}

	RESULT dtTexture::StartUp(const std::vector<soString>& _FilePath)
	{
		glGenTextures(1, &m_GLHandleID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_GLHandleID);

		for (GLuint i = 0; i < _FilePath.size(); i++)
		{
			printf("Load %s File Path \n", ws2s(_FilePath.at(i)).c_str());
			Load(_FilePath.at(i));
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);

			printf("%s Correct \n", ws2s(_FilePath.at(i)).c_str());
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		// Generate mipmaps for the texture.
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		// Release software data
		SOIL_free_image_data(m_TextureData);

		m_Target = GL_TEXTURE_CUBE_MAP;

		//Unbind texture buffer
		glBindTexture(GL_TEXTURE_2D, 0);

		return EC_OK;
	}

	void dtTexture::ShutDown()
	{
		//Release all the class resources 
		if (m_GLHandleID != 0)
		{
			glDeleteTextures(1, &m_GLHandleID);
			m_GLHandleID = 0;
		}		
	}

	RESULT dtTexture::Load(const soString& _FilePath)
	{
		GLint Test;
		m_TextureData = SOIL_load_image(ws2s(_FilePath).c_str(), &m_Width, &m_Height, &Test, SOIL_LOAD_RGBA);

		if (!m_TextureData)
		{
			SOE_OutputLOG("dtTexture", "Load()", "FAIL to load texture from file.");
			return EC_FALSE
		}

		return EC_OK;
	}
}