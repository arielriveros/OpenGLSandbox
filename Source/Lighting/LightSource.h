#pragma once
#include <glm/glm.hpp>
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"

class LightSource
{
private:
	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Shader m_Shader;
	glm::mat4 m_Transform;
	glm::vec4 m_Color;

public:
	LightSource(std::vector<float> vertices, std::vector<unsigned int> indices, const glm::vec4& color, const Shader& shader);
	~LightSource();

	void Draw(const Camera& camera) const;

	inline glm::vec4 GetColor() const { return m_Color; }
	inline void SetColor(const glm::vec4& color) { m_Color = color; }

	inline glm::mat4 GetTransform() const { return m_Transform; }
	inline void SetTransform(const glm::mat4& transform) { m_Transform = transform; }
};