#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	m_VAO = VertexArray();
	m_VBO = VertexBuffer();

	std::vector<float> vertices = {
		-0.1, -0.1, 0.0, 0.0, 0.0,
		 0.1,  0.1, 0.0, 1.0, 1.0,
		 0.1, -0.1, 0.0, 0.0, 1.0,
		-0.1,  0.1, 0.0, 1.0, 0.0
	};

	unsigned int size = vertices.size() * sizeof(vertices[0]);
	m_VBO.UploadData(&vertices[0], size);

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(2); // UV Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	std::vector<unsigned int> indices = { 0, 1, 2, 1, 3, 0 };
	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], indices.size());

	m_Texture = Texture("Resources/Images/light_icon.png", false);

	m_VBO.Unbind();
	m_IBO.Unbind();
}

DirectionalLight::~DirectionalLight()
{
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
	m_Texture.Unbind();

	m_VAO.Delete();
	m_VBO.Delete();
	m_IBO.Delete();
	m_Texture.Delete();
}

void DirectionalLight::Draw(const Camera& camera, const Shader& shader) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	shader.Bind();
	glEnable(GL_BLEND);
	m_Texture.Bind();
	shader.SetMat4("u_model", glm::mat4(1.0f));
	shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	shader.SetVec3("u_cameraPos", camera.Position);
	shader.SetVec3("u_color", Diffuse);

	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
}