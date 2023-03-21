#include "LightSource.h"

LightSource::LightSource(std::vector<float> vertices, std::vector<unsigned int> indices, const glm::vec4& color, const Shader& shader)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Shader = shader;
	m_Color = color;

	m_VAO = VertexArray();
	m_VBO = VertexBuffer();

	unsigned int size = vertices.size() * sizeof(vertices[0]);
	m_VBO.UploadData(&vertices[0], size);

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], indices.size());

	m_Transform = glm::mat4(1.0);
	m_Shader.SetMat4("u_model", m_Transform);
	m_Shader.SetVec4("u_lightColor", m_Color);

	m_Shader.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
}

LightSource::~LightSource()
{
	m_Shader.Unbind();
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();

	m_VAO.Delete();
	m_VBO.Delete();
	m_IBO.Delete();
}

void LightSource::Draw(const Camera& camera) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	m_Shader.Bind();
	m_Shader.SetMat4("u_model", m_Transform);
	m_Shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	m_Shader.SetVec4("u_lightColor", m_Color);

	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}