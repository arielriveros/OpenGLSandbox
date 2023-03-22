#include "Mesh.h"


Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, const std::string& texturePath, const Shader& shader)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Shader = shader;
	
	m_VAO = VertexArray();
	m_VBO = VertexBuffer();
	m_VBO.UploadData(&vertices[0], vertices.size() * sizeof(vertices[0]));
	
	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	layout.Push<float>(2); // UV Attribute
	layout.Push<float>(3); // Normal Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&indices[0], indices.size());

	m_Texture = Texture(texturePath, true);
	
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
	m_VBO.UploadData(&vertices[0], vertices.size() * sizeof(vertices[0]));

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
	m_Shader.SetInts("u_Texture", { 0 });

	m_Shader.SetMat4("u_model", GetTransform());
	m_Shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	m_Shader.SetVec3("u_lightColor", light.GetColor());
	m_Shader.SetVec3("u_lightPos", light.Position);
	
	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

glm::mat4 Mesh::GetTransform() const
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
