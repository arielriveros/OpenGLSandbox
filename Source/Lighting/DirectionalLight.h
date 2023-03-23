#pragma once
#include <glm/glm.hpp>
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Texture/Texture.h"

class DirectionalLight
{
public:
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Diffuse = glm::vec3(1.0f);
	glm::vec3 Ambient = glm::vec3(0.2f);
	glm::vec3 Specular = glm::vec3(1.0f);


private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Texture m_Texture;

public:
	DirectionalLight();
	~DirectionalLight();

	void Draw(const Camera& camera, const Shader& shader) const;
};