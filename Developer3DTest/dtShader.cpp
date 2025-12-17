/************************************************************************/
/**
* @LC	  4/10/2016
* @file   dtShader.h
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2016
* @brief  dtShader.h
of shaders
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

/************************************************************************/
/* Header include files									                */
/************************************************************************/
#include <GL/glew.h>
#include "dtShader.h"

namespace DeveloperTest
{
	/************************************************************************/
	/* dtShader class declaration					                        */
	/************************************************************************/
	DeveloperTest::dtShader::dtShader()
	{
		m_ShaderBuffer = NULL;
		m_GLHandleID = 0;
	}

	dtShader::~dtShader()
	{

	}

	RESULT dtShader::LoadShaderSourceFile(const char* _FilePath)
	{
		std::ifstream fin;
		int fileSize;
		char input;

		// Open the shader source file.
		fin.open(_FilePath);

		// If it could not open the file then exit.
		if (fin.fail())
		{
			SOE_ThrowException("dtShader", "LoadShaderSourceFile()", "Source file can not be reading");
			return EC_FALSE;
		}

		// Initialize the size of the file.
		fileSize = 0;

		// Read the first element of the file.
		fin.get(input);

		// Count the number of elements in the text file.
		while (!fin.eof())
		{
			fileSize++;
			fin.get(input);
		}

		// Close the file for now.
		fin.close();

		// Initialize the buffer to read the shader source file into.
		m_ShaderBuffer = SOE_NEW char[fileSize + 1];
		if (!m_ShaderBuffer)
		{
			SOE_ThrowException("dtShader", "LoadShaderSourceFile()", "Shader buffer creation error");
			return EC_FALSE;
		}

		// Open the shader source file again.
		fin.open(_FilePath);

		// Read the shader text file into the buffer as a block.
		fin.read(m_ShaderBuffer, fileSize);

		// Close the file.
		fin.close();

		// Null terminate the buffer.
		m_ShaderBuffer[fileSize] = '\0';

		return EC_OK;
	}
	
	void dtShader::OutputShaderErrorMessage()
	{
		int logSize;
		char* infoLog;

		// Get the size of the string containing the information log for the failed shader compilation message.
		glGetShaderiv(m_GLHandleID, GL_INFO_LOG_LENGTH, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = SOE_NEW char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		glGetShaderInfoLog(m_GLHandleID, logSize, NULL, infoLog);

		// Output error msg in output console
		SOE_OutputLOG("dtShader", "CompileShaderFromFile", infoLog);

		//Release info log
		SAFE_DELETE_ARRAY(infoLog);
	}

	RESULT dtShader::CompileShaderFromFile(const soString& _FilePath, uint32 _GLShaderTypeFlag)
	{
		int Status = 0;

		// Load the shader source file into a text buffer.
		if (FAIL(LoadShaderSourceFile(ws2s(_FilePath).c_str())))
		{
			return EC_FALSE;
		}

		// Create a shader object.
		m_GLHandleID = glCreateShader(_GLShaderTypeFlag);

		// Copy the shader source code strings into the shader objects.
		glShaderSource(m_GLHandleID, 1, &m_ShaderBuffer, NULL);
				
		// Compile the shaders.
		glCompileShader(m_GLHandleID);

		// Check to see if the shader compiled successfully.
		glGetShaderiv(m_GLHandleID, GL_COMPILE_STATUS, &Status);
		if (Status != 1)
		{
			// If it did not compile then write the syntax error message out to a text file for review.
			OutputShaderErrorMessage();
			SOE_ThrowException("dtShader", "CompileShaderFromFile()", "Compile error");
			return EC_FALSE;
		}

		return EC_OK;
	}

	void dtShader::ShutDown()
	{
		// Release the shader buffers.
		SAFE_DELETE_ARRAY(m_ShaderBuffer);
	}

	RESULT dtShader::StartUp(const soString& _FilePah, uint32 _GLShaderTypeFlag)
	{
		// Compile shader file
		if (FAIL(CompileShaderFromFile(_FilePah, _GLShaderTypeFlag)))
		{
			return EC_FALSE;
		}

		return EC_OK;
	}

}