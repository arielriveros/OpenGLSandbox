#pragma once
#include <glm/glm.hpp>
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../../Camera/Camera.h"

class Sprite
{
public:
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 EulerRotation = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);

	glm::vec3 Color = glm::vec3(1.0f);

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Texture m_Texture;

public:
	Sprite(const std::string& texturePath, const std::string& textureFileName);
	~Sprite();

	void Draw(const Camera& camera, const Shader& shader) const;

	glm::mat4 GetTransform() const;

};