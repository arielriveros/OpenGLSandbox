#include "Mesh.h"

Mesh::Mesh(const Geometry& geometry, const Material& material)
{
	m_Vertices = geometry.vertices;
	m_Indices = geometry.indices;

	m_AlbedoTexture = Texture(material.albedoPath, true);
	m_AlbedoColor = material.albedo;
	m_SpecularColor = material.specular;
	m_Shininess = material.shininess;

	m_VAO = VertexArray();
	m_VBO = VertexBuffer();
	m_VBO.UploadData(&m_Vertices[0], m_Vertices.size() * sizeof(m_Vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Normal Attribute
	layout.Push<float>(2); // UV Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&m_Indices[0], m_Indices.size());

	m_VBO.Unbind();
	m_IBO.Unbind();
	m_AlbedoTexture.Unbind();
}

Mesh::~Mesh()
{
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
	m_AlbedoTexture.Unbind();

	m_VAO.Delete();
	m_VBO.Delete();
	m_IBO.Delete();
	m_AlbedoTexture.Delete();
}

void Mesh::Draw(const Camera& camera, const Shader& shader) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	shader.Bind();
	m_AlbedoTexture.Bind();
	shader.SetInts("u_material.albedoTexture", { 0 });
	shader.SetVec3("u_material.albedo", m_AlbedoColor);
	shader.SetVec3("u_material.specular", m_SpecularColor);
	shader.SetFloats("u_material.shininess", { m_Shininess });

	shader.SetMat4("u_model", GetTransform());

	shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	shader.SetVec3("u_cameraPos", camera.Position);

	
	
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
