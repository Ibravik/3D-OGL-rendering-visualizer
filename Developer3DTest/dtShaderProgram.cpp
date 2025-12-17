/********************************************************************/
/**
* @LC	  4/10/2016
* @file   dtShaderProgram.cpp
* @Author Aldo Muñoz (lehi.munoz@gmail.com)
* @date   4/9/2016
* @brief  dtShaderProgram class definition
* @bug	  No known bugs.
*/
/********************************************************************/

/************************************************************************/
/* Header files inclusion									            */
/************************************************************************/
#include "dtOGLManager.h"
#include "dtShaderProgram.h"

/************************************************************************/
/* dtIndexBuffer definition								                */
/************************************************************************/
namespace DeveloperTest
{
	dtShaderProgram::dtShaderProgram()
	{
		m_GLHandleID = 0;
	}

	dtShaderProgram::~dtShaderProgram()
	{
		ShutDown();
	}

	void dtShaderProgram::OutputLinkerErrorMessage()
	{
		int logSize;
		char* infoLog;

		// Get the size of the string containing the information log for the failed shader compilation message.
		glGetProgramiv(m_GLHandleID, GL_INFO_LOG_LENGTH, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = SOE_NEW char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		glGetProgramInfoLog(m_GLHandleID, logSize, NULL, infoLog);

		// Output error msg in output console
		SOE_OutputLOG("dtShader", "CompileShaderFromFile", infoLog);

		//Release info log
		SAFE_DELETE_ARRAY(infoLog);
	}

	void dtShaderProgram::ShutDown()
	{
		// Detach the vertex and fragment shaders from the program.
		glDetachShader(m_GLHandleID, m_VertexShader.m_GLHandleID);
		glDetachShader(m_GLHandleID, m_FragmentShader.m_GLHandleID);

		// Delete the vertex and fragment shaders.
		glDeleteShader(m_VertexShader.m_GLHandleID);
		glDeleteShader(m_FragmentShader.m_GLHandleID);

		// Delete the shader program.
		glDeleteProgram(m_GLHandleID);
	}

	RESULT dtShaderProgram::StartUp(const soString& _VSFilePath, const soString& _PSFilePath)
	{
		int Status;

		// Compile the shader programs
		if (FAIL(m_VertexShader.StartUp(_VSFilePath, GL_VERTEX_SHADER)))
		{
			return EC_FALSE;
		}

		if (FAIL(m_FragmentShader.StartUp(_PSFilePath, GL_FRAGMENT_SHADER)))
		{
			return EC_FALSE;
		}

		// Create a shader program object.
		m_GLHandleID = glCreateProgram();
		
		// Attach the vertex and fragment shader to the program object.
		glAttachShader(m_GLHandleID, m_VertexShader.m_GLHandleID);
		glAttachShader(m_GLHandleID, m_FragmentShader.m_GLHandleID);

		// Bind the shader input variables.
		glBindAttribLocation(m_GLHandleID, 0, "inPosition");
		glBindAttribLocation(m_GLHandleID, 1, "inTexCoord");
		glBindAttribLocation(m_GLHandleID, 2, "inNormal");
		glBindAttribLocation(m_GLHandleID, 3, "inBinormal");
		glBindAttribLocation(m_GLHandleID, 4, "inTangent");

		// Link the shader program.
		glLinkProgram(m_GLHandleID);

		// Check the status of the link.
		glGetProgramiv(m_GLHandleID, GL_LINK_STATUS, &Status);
		if (Status != 1)
		{
			// If it did not link then write the syntax error message out to a text file for review.
			OutputLinkerErrorMessage();
			SOE_ThrowException("dtShaderProgram", "StartUp", "Link program error");
			return EC_FALSE;
		}

		return EC_OK;
	}

	void dtShaderProgram::SetShader()
	{
		glUseProgram(m_GLHandleID);
	}

	RESULT dtShaderProgram::SetShaderParameters(const ShaderParameters& _ShaderParameters)
	{
		uint32 location;

		// SkyBox Transform
		location = glGetUniformLocation(m_GLHandleID, "SBT");
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, false, &_ShaderParameters.SkyBoxTransform.m00);
		}
		
		// View Matrix
		location = glGetUniformLocation(m_GLHandleID, "VM");
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, false, &_ShaderParameters.VM.m00);
		}
		
		// Proj Matrix
		location = glGetUniformLocation(m_GLHandleID, "PM");
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, false, &_ShaderParameters.PM.m00);
		}

		// Proj Matrix
		location = glGetUniformLocation(m_GLHandleID, "RM");
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, false, &_ShaderParameters.RM.m00);
		}

		// shadow View Matrix
		location = glGetUniformLocation(m_GLHandleID, "SVM");
		if (location != -1)
		{
			glm::mat4 rotation = glm::rotate(_ShaderParameters.Delta, glm::vec3(1, 0, 0));
			glm::vec4 lD = rotation * glm::vec4(-10.0f, 5.0f, -10.0f, 1.0f);
			glUniformMatrix4fv(location, 1, false, &glm::lookAt(glm::vec3(lD[0], lD[1], lD[2]), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))[0][0]);
		}

		// shadow Proj Matrix
		location = glGetUniformLocation(m_GLHandleID, "SPM");
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, false, &glm::ortho<float>(-10, 10, -10, 10, -10, 20)[0][0]);
		}
		
		// Camera Pos.
		location = glGetUniformLocation(m_GLHandleID, "VP");
		if (location != -1)
		{
			glUniform3fv(location, 1, &_ShaderParameters.VP.a);
		}
		
		// Scene Light Color
		location = glGetUniformLocation(m_GLHandleID, "SLC");
		if (location != -1)
		{
			glUniform4fv(location, 1, &_ShaderParameters.SLC.a);
		}

		// Scene light dir
		location = glGetUniformLocation(m_GLHandleID, "SLD");
		if (location != -1)
		{
			glm::mat4 rotation = glm::rotate(_ShaderParameters.Delta, glm::vec3(1, 0, 0));
			glm::vec4 lD = rotation * glm::vec4(-10.0f, 5.0f, -10.0f, 1.0f);
			glUniform3fv(location, 1, &glm::vec3(lD[0], lD[1], lD[2])[0]);
		}

		// Camera Light Inner Cone
		location = glGetUniformLocation(m_GLHandleID, "CIC");
		if (location != -1)
		{
			glUniform1fv(location, 1, &_ShaderParameters.CIC);
		}

		// Camera Light Out Cone
		location = glGetUniformLocation(m_GLHandleID, "COC");
		if (location != -1)
		{
			glUniform1fv(location, 1, &_ShaderParameters.COC);
		}

		// Camera light pos
		location = glGetUniformLocation(m_GLHandleID, "CLP");
		if (location != -1)
		{
			glUniform3fv(location, 1, &_ShaderParameters.CLP.a);
		}

		// Camera Light Color
		location = glGetUniformLocation(m_GLHandleID, "CLC");
		if (location != -1)
		{
			glUniform4fv(location, 1, &_ShaderParameters.CLC.a);
		}

		// Camera light dir
		location = glGetUniformLocation(m_GLHandleID, "CLD");
		if (location != -1)
		{
			glUniform3fv(location, 1, &_ShaderParameters.CLD.a);
		}
		
		// Mip level
		location = glGetUniformLocation(m_GLHandleID, "ML");
		if (location != -1)
		{
			glUniform1iv(location, 1, &_ShaderParameters.ML);
		}
	
		return EC_OK;
	}

}