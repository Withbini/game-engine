#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "Math.hpp"

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// if geometry shader path is present, also load a geometry shader
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		mVertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(mVertexShader, 1, &vShaderCode, NULL);
		glCompileShader(mVertexShader);
		checkCompileErrors(mVertexShader, "VERTEX");
		mFragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(mFragShader, 1, &fShaderCode, NULL);
		glCompileShader(mFragShader);
		checkCompileErrors(mFragShader, "FRAGMENT");

		if (geometryPath != nullptr)
		{
			const char * gShaderCode = geometryCode.c_str();
			mGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(mGeometryShader, 1, &gShaderCode, NULL);
			glCompileShader(mGeometryShader);
			checkCompileErrors(mGeometryShader, "GEOMETRY");
		}

		ID = glCreateProgram();
		glAttachShader(ID, mVertexShader);
		glAttachShader(ID, mFragShader);
		if (geometryPath != nullptr)
			glAttachShader(ID, mGeometryShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
	}
	~Shader()
	{
		glDeleteProgram(ID);
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragShader);

		if (mGeometryShader != 0)
			glDeleteShader(mGeometryShader);
	}

	void Bind()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	/*void setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}*/
	void setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	/*void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}*/
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec3(const std::string &name, const Vector3 &value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value.GetAsFloatPtr());
	}

	/*void setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}*/
	void setVec4(const std::string &name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	/*void setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
	}

	void setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
	}

	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, &mat[0][0]);
	}*/

	void setMat4(const std::string &name, const Matrix4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, mat.GetAsFloatPtr());
	}

private:
	// utility
	static void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				SDL_Log("ERROR::SHADER_COMPILATION_ERROR of type: %s \n %s \n -- --------------------------------------------------- --\n", type.c_str(), infoLog);
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				SDL_Log("ERROR::PROGRAM_LINKING_ERROR of type: %s \n %s \n -- --------------------------------------------------- --\n", type.c_str(), infoLog);
			}
		}
	}
	unsigned int mFragShader;
	unsigned int mVertexShader;
	unsigned int mGeometryShader;
};