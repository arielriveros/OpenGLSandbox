#pragma once
#include <glm/glm.hpp>
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"

class LightSource
{
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 EulerRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

private:
	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Shader m_Shader;
	glm::vec3 m_Color;

public:
	LightSource(std::vector<float> vertices, std::vector<unsigned int> indices, const glm::vec3& color, const Shader& shader);
	~LightSource();

	void Draw(const Camera& camera) const;

	inline glm::vec3 GetColor() const { return m_Color; }
	inline void SetColor(const glm::vec3& color) { m_Color = color; }

	glm::mat4 GetTransform() const;
	
};