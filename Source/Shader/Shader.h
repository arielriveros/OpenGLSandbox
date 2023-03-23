#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	void SetMat4(const std::string& uniformName, glm::mat4 value) const;
	void SetVec2(const std::string& uniformName, glm::vec2 value) const;
	void SetVec3(const std::string& uniformName, glm::vec3 value) const;
	void SetVec4(const std::string& uniformName, glm::vec4 value) const;

private:
	std::string LoadSource(const char* shaderPath);
};