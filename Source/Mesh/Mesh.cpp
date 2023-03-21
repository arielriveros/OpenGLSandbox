#include "Mesh.h"


Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const std::string& texturePath, const Shader& shader)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Shader = shader;
	
	m_VAO = VertexArray();
	
	m_VBO = VertexBuffer();

	unsigned int size = vertices.size() * sizeof(vertices[0]);
	m_VBO.UploadData(&vertices[0], size);
	
	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	layout.Push<float>(2); // UV Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], indices.size());

	m_Texture = Texture(texturePath);
	m_Texture.Bind();
	m_Shader.SetInts("u_Texture", { 0 });
	
	m_Transform = glm::mat4(1.0);
	m_Shader.SetMat4("u_model", m_Transform);
	
	m_Shader.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
}

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const Shader& shader)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Shader = shader;

	m_VAO = VertexArray();

	m_VBO = VertexBuffer();
	unsigned int size = vertices.size() * sizeof(vertices[0]);
	m_VBO.UploadData(&vertices[0], size);

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], indices.size());

	m_Shader.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
}

Mesh::~Mesh()
{
	m_Shader.Unbind();
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
	m_Texture.Unbind();

	m_VAO.Delete();
	m_VBO.Delete();
	m_IBO.Delete();
	m_Texture.Delete();
}

void Mesh::Draw(const Camera& camera, const LightSource& light) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	m_Shader.Bind();
	m_Texture.Bind();
	m_Shader.SetMat4("u_model", m_Transform);
	m_Shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	m_Shader.SetVec4("u_lightColor", light.GetColor());
	
	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}