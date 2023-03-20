#pragma once
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include <vector>

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
	
public:
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const Texture &texture, const Shader &shader);
	~Mesh();
	
	void Draw() const;
};