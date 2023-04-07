#include "Mesh.h"
#include <string>
#include <imgui.h>
#include "../GUI/Editor.h"

const float PI = 3.1415926535f;

Mesh::Mesh()
{
	m_Name = "mesh";
	m_Empty = true;
	m_Material = nullptr;
	m_NoTextures = true;
}

Mesh::Mesh(const std::string name)
{
	m_Name = name;
	m_Empty = true;
	m_Material = nullptr;
	m_NoTextures = true;
}

Mesh::Mesh(const std::string name, const Geometry& geometry)
{
	m_Name = name;
	m_Empty = false;
	SetUpVertexArray(geometry.vertices, geometry.indices);
	SetUpMaterial(Material());
}

Mesh::Mesh(const std::string name, const Geometry& geometry, const Material& material)
{
	m_Name = name;
	m_Empty = false;
	m_Material = &material;
	SetUpVertexArray(geometry.vertices, geometry.indices);
	SetUpMaterial(material);
}

Mesh::Mesh(const std::string name, const Geometry& geometry, const std::vector<Texture>& textures)
{
	m_Name = name;
	m_Empty = false;
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
	if (!m_Empty)
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
				m_Textures[i].Activate(i); // active proper texture unit before binding
				std::string name;

				if (m_Textures[i].type == "texture_diffuse")
				{
					name = "texture_diffuse" + std::to_string(diffuseIndex);
					diffuseIndex++;
				}
				else if (m_Textures[i].type == "texture_specular")
				{
					name = "texture_specular" + std::to_string(specularIndex);
					specularIndex++;
				}
				else if (m_Textures[i].type == "texture_normal")
				{
					name = "texture_normal" + std::to_string(normalIndex);
					shader.SetBool("u_noNormalMap", false);
					normalIndex++;
				}
				else
					name = m_Textures[i].name;

				shader.SetInt(name, i);
				// Bind the texture
				m_Textures[i].Bind();
			}

			shader.SetBool("u_noTex", false);
		}

		shader.SetMat4("u_model", ModelTransform.ModelMatrix);
		shader.SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
		shader.SetVec3("u_cameraPos", camera.Position);
	
		unsigned int count = m_IBO.GetCount();
		glEnable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	for (Mesh* child : children)
		child->Draw(camera, shader);
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

void Mesh::AddChild(Mesh* mesh)
{
	mesh->parent = this;
	children.push_back(mesh);
}

void Mesh::Update()
{
	ModelTransform.Position = Position;
	ModelTransform.EulerRotation = Rotation;
	ModelTransform.Scale = Scale;

	if (!parent)
	{
		ModelTransform.ComputeModelMatrix();
	}
	else
	{
		ModelTransform.ComputeModelMatrix(parent->ModelTransform.ModelMatrix);
	}

	for (Mesh* child : children)
		child->Update();
}

void Mesh::OnGui()
{
	ImGui::Text(m_Name.c_str());

	AxisWidget(m_Name, "Position", &Position.x, &Position.y, &Position.z);
	AxisWidget(m_Name, "Rotation", &Rotation.x, &Rotation.y, &Rotation.z);
	AxisWidget(m_Name, "Scale   ", &Scale.x, &Scale.y, &Scale.z);

	if (!children.empty())
	{
		if (ImGui::TreeNode((m_Name + " Children").c_str()))
		{
			for (Mesh* child : children)
				child->OnGui();
			ImGui::TreePop();
			ImGui::Spacing();
		}
	}

	ImGui::Separator();
}

void Mesh::SetUpVertexArray(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_Vertices = vertices;
	m_Indices = indices;

	m_VAO = VertexArray();
	m_VBO = VertexBuffer();
	m_VBO.UploadData(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));

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