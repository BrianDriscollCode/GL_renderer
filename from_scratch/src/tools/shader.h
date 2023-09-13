#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "debugOutput.h"

#include "./libraries/glm/glm.hpp"
#include "./libraries/glm/gtc/matrix_transform.hpp"
#include "./libraries/glm/gtc/type_ptr.hpp"

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath)
	{
		DebugOutput debugOutput(true);

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		//open file, read stream buffer, store file string
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			debugOutput.outputGreenText("**SUCCESS**::SHADER::FILE_READ_SUCCESSFULLY::[tools/shader.h]");
			std::cout << "VERTEX SHADER PATH: " << vertexPath << std::endl;
			std::cout << "FRAGMENT SHADER PATH: " << fragmentPath << std::endl;
		}
		catch (std::ifstream::failure& e)
		{
			debugOutput.outputRedText("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ::[tools / shader.h]");
			debugOutput.outputRedText(e.what());
			std::cout << "VERTEX SHADER PATH: " << vertexPath << std::endl;
			std::cout << "FRAGMENT SHADER PATH: " << fragmentPath << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex;
		unsigned int fragment;

		// compile vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		//check vertex shader success
		int success;
		char infoLog[512];
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			debugOutput.outputRedText("ERROR::SHADER::VERTEX::COMPILATION_FAILED::[tools/shader.h]");
			debugOutput.outputRedText(infoLog);

		}
		else 
		{
			debugOutput.outputGreenText("**SUCCESS**::SHADER::VERTEX::COMPILED::[tools/shader.h]");
		}

		// compile fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			debugOutput.outputRedText("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED::[tools/shader.h]");
			debugOutput.outputRedText(infoLog);
		}
		else
		{
			debugOutput.outputGreenText("**SUCCESS**::SHADER::FRAGMENT::COMPILED::[tools/shader.h]");
		}

		// Create program object

		ID = glCreateProgram();
		
		// Link shaders to program
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetShaderiv(fragment, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			debugOutput.outputRedText("ERROR::SHADER::PROGRAM_LINK::LINKING_FAILED::[tools/shader.h]");
			debugOutput.outputRedText(infoLog);
		}
		else
		{
			debugOutput.outputGreenText("**SUCCESS**::SHADER::PROGRAM::LINKED::[tools/shader.h]");
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use()
	{
		glUseProgram(ID);
	}
	// utility functions

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		std::cout << glGetUniformLocation(ID, name.c_str()) << " -setInt" << value << std::endl;
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		std::cout << glGetUniformLocation(ID, name.c_str()) << " -setFloat" << value << std::endl;
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		std::cout << glGetUniformLocation(ID, name.c_str()) << " -setVec4" << std::endl;
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
};


#endif