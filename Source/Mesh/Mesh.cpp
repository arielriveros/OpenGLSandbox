#include "Mesh.h"
#include <string>

Mesh::Mesh(const Geometry& geometry, const Material& material)
{
	m_Material = &material;
	SetUpVertexArray(geometry.vertices, geometry.indices);
	SetUpMaterial(material);
}

Mesh::Mesh(const Geometry& geometry, const std::vector<Texture>& textures)
{
	m_Textures = textures;
	SetUpVertexArray(geometry.vertices, geometry.indices);
	SetUpTextures(textures);
}

Mesh::~Mesh()
{
	//delete m_Material;
}

void Mesh::Draw(const Camera& camera, const Shader& shader) const
{
	m_VAO.Bind();
	m_IBO.Bind();
	shader.Bind();

	shader.SetBool("u_noNormalMap", true);

	if (m_NoTextures) {
		shader.SetVec3("u_material.diffuse",    m_Material->diffuse);
		shader.SetVec3("u_material.specular",   m_Material->specular);
		shader.SetFloat("u_material.shininess", m_Material->shininess);
		shader.SetBool("u_noTex", true);
	}
	else
	{
		unsigned int diffuseIndex  = 0;
		unsigned int specularIndex = 0;
		unsigned int normalIndex   = 0;

		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			std::string name;

			if (m_Textures[i].type == "texture_diffuse")
				name = std::to_string(diffuseIndex++);
			else if (m_Textures[i].type == "texture_specular")
				name = std::to_string(specularIndex++);
			else if (m_Textures[i].type == "texture_normal")
				name = std::to_string(specularIndex++);
			else
				name = m_Textures[i].name;

			shader.SetInt(name, i);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, m_Textures[i].ID());
		}

		shader.SetBool("u_noTex", false);
	}

	shader.SetMat4("u_model", GetTransform());
	shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	shader.SetVec3("u_cameraPos", camera.Position);
	
	unsigned int count = m_IBO.GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Destroy()
{
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();

	m_VAO.Delete();
	m_VBO.Delete();
	m_IBO.Delete();
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

void Mesh::SetUpVertexArray(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_Vertices = vertices;
	m_Indices = indices;

	m_VAO = VertexArray();
	m_VBO = VertexBuffer();
	m_VBO.UploadData(&m_Vertices[0], m_Vertices.size() * sizeof(m_Vertices[0]));

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Normal Attribute
	layout.Push<float>(2); // UV Attribute
	layout.Push<float>(3); // Tangent Attribute
	layout.Push<float>(3); // Bitangent Attribute
	m_VAO.AttachVertexBuffer(m_VBO, layout);

	m_IBO = IndexBuffer();
	m_IBO.UploadData(&m_Indices[0], m_Indices.size());

	m_VBO.Unbind();
	m_IBO.Unbind();
}

void Mesh::SetUpMaterial(const Material& material)
{
	m_NoTextures = true;
	m_Material = &material;
}
void Mesh::SetUpTextures(const std::vector<Texture>& textures)
{
	m_NoTextures = false;
	m_Textures.insert(m_Textures.end(), textures.begin(), textures.end());
}