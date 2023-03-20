#pragma once
#include <iostream>
#include <vector>

class Shader
{
private:
	unsigned int	m_shaderProgramID;
	unsigned int	m_vsID;
	unsigned int	m_fsID;
	std::string		m_vertexSource;
	std::string		m_fragmentSource;
	
public:
	Shader() {};
	Shader(const char* vsPath, const char* fsPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	void SetInts(const std::string& uniformName, std::vector<int> values) const;
	void SetFloats(const std::string& uniformName, std::vector<float> values) const;

private:
	std::string LoadSource(const char* shaderPath);
};