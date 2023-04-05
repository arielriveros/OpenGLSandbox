#include "Sprite.h"

Sprite::Sprite(const std::string& texturePath, const std::string& textureFileName)
{
	m_VAO = VertexArray();
	m_VBO = VertexBuffer();

	std::vector<float> vertices = {
		-0.1f, -0.1f, 0.0f, 0.0f, 0.0f,
		 0.1f,  0.1f, 0.0f, 1.0f, 1.0f,
		 0.1f, -0.1f, 0.0f, 0.0f, 1.0f,
		-0.1f,  0.1f, 0.0f, 1.0f, 0.0f
	};

	unsigned int size = vertices.size() * sizeof(vertices[0]);
	m_VBO.UploadData(&vertices[0], size);

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(2); // UV Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	std::vector<unsigned int> indices = { 0, 2, 1, 0, 1, 3 };
	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], static_cast<unsigned int>(indices.size()));

	m_Texture = Texture(texturePath, textureFileName, "diffuse");

	m_VBO.Unbind();
	m_IBO.Unbind();
}

Sprite::~Sprite()
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

void Sprite::Draw(const Camera& camera, const Shader& shader) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	shader.Bind();
	glEnable(GL_BLEND);
	m_Texture.Bind();
	shader.SetMat4("u_model", GetTransform());
	shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	shader.SetVec3("u_cameraPos", camera.Position);
	shader.SetVec3("u_color", Color);

	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
}

glm::mat4 Sprite::GetTransform() const
{
	const glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), Position);

	const glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),
		EulerRotation.x,
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),
		EulerRotation.y,
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f),
		EulerRotation.z,
		glm::vec3(0.0f, 0.0f, 1.0f));

	const glm::mat4 rotationMatrix = rotY * rotX * rotZ;

	const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

	return transMatrix * rotationMatrix * scaleMatrix;
}
