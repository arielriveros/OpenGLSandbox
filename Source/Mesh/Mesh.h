#pragma once
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
private:
	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer m_IBO;
	Texture m_Texture;
	Shader m_Shader;
	glm::mat4 m_Transform;
	
public:
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const std::string& texturePath, const Shader &shader);
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const Shader& shader);
	~Mesh();
	
	void Draw() const;

	inline glm::mat4 GetTransform() const { return m_Transform; }
	void SetTransform(const glm::mat4& transform);
};