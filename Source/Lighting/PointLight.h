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

	glm::vec3 Diffuse = glm::vec3(0.5f);
	glm::vec3 Ambient = glm::vec3(0.2f);
	glm::vec3 Specular = glm::vec3(1.0f);

	float Constant = 1.0f;
	float Linear = 0.09f;
	float Quadratic = 0.032f;

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Texture m_Texture;

public:
	PointLight(glm::vec3 color);
	~PointLight();

	void Draw(const Camera& camera, const Shader& shader) const;

	glm::mat4 GetTransform() const;
	
};