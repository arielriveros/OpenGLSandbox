#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const Texture& texture, const Shader& shader)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Shader = shader;
	m_Texture = texture;
	
	m_VAO = VertexArray();
	
	m_VBO = VertexBuffer();
	m_VBO.UploadData(&vertices[0], sizeof(vertices) * sizeof(vertices[0]));
	
	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	layout.Push<float>(2); // UV Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], 6);

	m_Texture.Bind();
	m_Shader.SetInts("u_Texture", { 0 });
	
	m_Shader.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
}

Mesh::~Mesh()
{
	m_VAO.Unbind();
	m_Shader.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();

	m_VAO.Delete();
	m_VBO.Delete();
	m_IBO.Delete();
}

void Mesh::Draw() const
{
	m_VAO.Bind();
	m_IBO.Bind();
	m_Shader.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

