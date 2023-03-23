#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

Shader::Shader(const char* vsPath, const char* fsPath)
{
	m_vertexSource = LoadSource(vsPath);
	m_fragmentSource = LoadSource(fsPath);

	int success;
	char infoLog[512];

	const char* vertex = m_vertexSource.c_str();
	
	// Create vertex shader
	m_vsID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vsID, 1, &vertex, NULL);
	glCompileShader(m_vsID);
	
	// Vertex shader error checking
	glGetShaderiv(m_vsID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_vsID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
	}

	const char* fragment = m_fragmentSource.c_str();

	// Create fragment shader
	m_fsID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fsID, 1, &fragment, NULL);
	glCompileShader(m_fsID);
	
	// Fragment shader error checking
	glGetShaderiv(m_fsID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fsID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
	}

	m_shaderProgramID = glCreateProgram();
	glAttachShader(m_shaderProgramID, m_vsID);
	glAttachShader(m_shaderProgramID, m_fsID);
	glLinkProgram(m_shaderProgramID);
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(m_vsID);
	glDeleteShader(m_fsID);
}

void Shader::Bind() const
{
	glUseProgram(m_shaderProgramID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::Delete() const
{
	glDeleteProgram(m_shaderProgramID);
}


void Shader::SetInts(const std::string& uniformName, std::vector<int> values) const
{
	int uniformLocation = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Error: Uniform '" << uniformName << "' not found." << std::endl;
		return;
	}

	Bind();
	size_t length = values.size();
	switch (length)
	{
	case 0:
		std::cout << "Error: No value passed to uniform" << std::endl;
		break;
	case 1:
		glUniform1i(uniformLocation, values[0]);
		break;
	case 2:
		glUniform2i(uniformLocation, values[0], values[1]);
		break;
	case 3:
		glUniform3i(uniformLocation, values[0], values[1], values[2]);
		break;
	case 4:
		glUniform4i(uniformLocation, values[0], values[1], values[2], values[3]);
		break;
	default:
		std::cout << "Error: Invalid value passed to uniform" << std::endl;
	}
}

void Shader::SetFloats(const std::string& uniformName, std::vector<float> values) const
{
	int uniformLocation = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Error: Uniform '" << uniformName << "' not found." << std::endl;
		return;
	}

	Bind();
	size_t length = values.size();
	switch (length)
	{
		case 0:
			std::cout << "Error: No value passed to uniform" << std::endl;
			break;
		case 1:
			glUniform1f(uniformLocation, values[0]);
			break;
		case 2:
			glUniform2f(uniformLocation, values[0], values[1]);
			break;
		case 3:
			glUniform3f(uniformLocation, values[0], values[1], values[2]);
			break;
		case 4:
			glUniform4f(uniformLocation, values[0], values[1], values[2], values[3]);
			break;
		default:
			std::cout << "Error: Invalid value passed to uniform" << std::endl;
	}
}

void Shader::SetMat4(const std::string& uniformName, glm::mat4 value) const
{
	int uniformLocation = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Error: Uniform '" << uniformName << "' not found." << std::endl;
		return;
	}

	Bind();
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec2(const std::string& uniformName, glm::vec2 value) const
{
	int uniformLocation = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Error: Uniform '" << uniformName << "' not found." << std::endl;
		return;
	}

	Bind();
	glUniform2fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& uniformName, glm::vec3 value) const
{
	int uniformLocation = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Error: Uniform '" << uniformName << "' not found." << std::endl;
		return;
	}

	Bind();
	glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetVec4(const std::string& uniformName, glm::vec4 value) const
{
	int uniformLocation = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (uniformLocation == -1)
	{
		std::cout << "Error: Uniform '" << uniformName << "' not found." << std::endl;
		return;
	}

	Bind();
	glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
}

std::string Shader::LoadSource(const char* shaderPath)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}


	return shaderCode;
}