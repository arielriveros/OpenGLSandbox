#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int	m_shaderProgramID = 0;
	unsigned int	m_vsID = 0;
	unsigned int	m_fsID = 0;
	std::string		m_vertexSource;
	std::string		m_fragmentSource;
	
public:
	Shader() {};
	Shader(const char* vsPath, const char* fsPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	void SetInt(const std::string& uniformName, unsigned int value) const;
	void SetFloat(const std::string& uniformName, float value) const;
	void SetBool(const std::string& uniformName, bool value) const;

	void SetMat4(const std::string& uniformName, glm::mat4 value) const;
	void SetVec2(const std::string& uniformName, glm::vec2 value) const;
	void SetVec3(const std::string& uniformName, glm::vec3 value) const;
	void SetVec4(const std::string& uniformName, glm::vec4 value) const;

private:
	std::string LoadSource(const char* shaderPath);
	int GetUniform(const std::string& uniformName) const;
};