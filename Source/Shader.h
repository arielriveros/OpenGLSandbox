#pragma once
#include <iostream>

class Shader
{
private:
	unsigned int	m_shaderProgramID;
	unsigned int	m_vsID;
	unsigned int	m_fsID;
	std::string		m_vertexSource;
	std::string		m_fragmentSource;
	
public:
	Shader();
	Shader(const char* vsPath, const char* fsPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	std::string LoadSource(const char* shaderPath);
};