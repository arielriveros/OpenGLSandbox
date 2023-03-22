#pragma once
#include <glm/glm.hpp>
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Texture/Texture.h"

class PointLight
{
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 EulerRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Texture m_Texture;

public:
	PointLight(const glm::vec3& color);
	~PointLight();

	void Draw(const Camera& camera, const Shader& shader) const;

	glm::mat4 GetTransform() const;
	
};