#pragma once
#include "../VertexArray/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
#include "../Camera/Camera.h"
#include "../Lighting/PointLight.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Geometry
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; 
};

struct Material
{
	glm::vec3 albedo   = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);

	std::string albedoPath	 = "Resources/Images/white.jpg";
	std::string specularPath = "Resources/Images/white.jpg";

	float shininess = 32.0f;

	glm::vec2 uv = glm::vec2(1.0f);
};

class Mesh
{
public:
	glm::vec3 Position	    = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 EulerRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale			= glm::vec3(1.0f, 1.0f, 1.0f);

private:
	std::vector<Vertex>		  m_Vertices;
	std::vector<unsigned int> m_Indices;
	VertexArray  m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer  m_IBO;

	Texture		m_AlbedoTexture;
	Texture		m_SpecularTexture;

	glm::vec3	m_AlbedoColor;
	glm::vec3	m_SpecularColor;

	float		m_Shininess;
	glm::vec2   m_uvModifier;
	
public:
	Mesh(const Geometry& geometry, const Material& material);
	~Mesh();
	
	void Draw(const Camera& camera, const Shader& shader) const;

	glm::mat4 GetTransform() const;
};