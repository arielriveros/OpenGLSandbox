#pragma once
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../Camera/Camera.h"
#include "../Lighting/PointLight.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Mesh
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
	Texture m_Texture;
	Shader m_Shader;
	
public:
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const std::string& texturePath, const Shader &shader);
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const Shader& shader);
	~Mesh();
	
	void Draw(const Camera& camera, const PointLight& light) const;

	glm::mat4 GetTransform() const;
};