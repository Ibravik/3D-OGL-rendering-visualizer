/********************************************************************/
/**
* @LC     4/7/2017
* @file   dtTexture.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/6/2017
* @brief  Definition of class dtTexture. It contain all the texture info
		  and GL buffer creation abstraction
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Header class inclusion								                */
/************************************************************************/
#include <Soul_Math.h>

using namespace SoulSDK;

namespace DeveloperTest
{
	/************************************************************************/
	/* Texture init data struct					                            */
	/************************************************************************/
	struct TextureData
	{
		soRect BufferSize;								/*!< Texture Size */
		int32 InternalFormat;							/*!< Texture internal format (i.e. GL_RGBA16F) */
		int32 Format;									/*!< Texture format (i.e. GL_RGBA) */
		int32 Type;										/*!< Texture Type (i.e GL_FLOAT) */		
		int32 AtachmentType;							/*!< Form that the texture relacionate with a frame buffer */
		uint32 SamplerID;								/*!< Atached sampler */

		TextureData()
		{
			SamplerID = 0;
			InternalFormat = 0;
			Type = 0;
		}
	};

	/************************************************************************/
	/* dtTexture class definition											*/
	/************************************************************************/
	class dtTexture
	{
	public:
		dtTexture();
		~dtTexture();

		/************************************************************************/
		/* Variables															*/
		/************************************************************************/
	private:
		unsigned char* m_TextureData;							/*!< All the texture data in software */
		int32 m_Width;											/*!< Texture width */
		int32 m_Height;											/*!< Texture Height */

	public:
		uint32 m_GLHandleID;									/*!< GL buffer id */
		uint32 m_SamplerID;										/*!< Atached sampler to this texture */
		uint8 m_TextureTypeID;									/*!< Texture type ID*/
		GLenum m_Target;										/*!< Texture target type */
		soString* m_Name;										/*!< Texture name */

		/************************************************************************/
		/* Funciones															*/
		/************************************************************************/
	private:
		RESULT Load(const soString& _FilePath);					/*!< Load the texture from file path */

	public:
		void ShutDown();										/*!< Free the class resources */
		RESULT StartUp(const soString& _FilePath);				/*!< Class init from file load */
		RESULT StartUp(const std::vector<soString>& _FilePath);	/*!< Class init from file load */
		RESULT StartUp(const TextureData& _TextureData);		/*!< Class init from empty data */
	};
}