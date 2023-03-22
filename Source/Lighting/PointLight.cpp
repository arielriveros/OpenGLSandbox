#include "PointLight.h"

PointLight::PointLight(const glm::vec3& color, const Shader& shader)
{
	m_Shader = shader;
	Color = color;

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

	m_Shader.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
}

PointLight::~PointLight()
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

void PointLight::Draw(const Camera& camera) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	m_Shader.Bind();
	glEnable(GL_BLEND);
	m_Texture.Bind();
	m_Shader.SetMat4("u_model", GetTransform());
	m_Shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	m_Shader.SetVec3("u_lightColor", Color);
	m_Shader.SetVec3("u_cameraPos", camera.Position);

	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
}

glm::mat4 PointLight::GetTransform() const
{
	const glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), Position);

	return transMatrix;
}
