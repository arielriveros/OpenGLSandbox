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

	glm::vec3 tangent;
	glm::vec3 biTangent;
};

struct Geometry
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; 
};

struct Material
{
	glm::vec3 ambient	= glm::vec3(1.0f);
	glm::vec3 diffuse	= glm::vec3(1.0f);
	glm::vec3 specular	= glm::vec3(1.0f);
	float shininess		= 32.0f;
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
	std::vector<Texture>	  m_Textures;

	VertexArray  m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer  m_IBO;

	const Material*	m_Material;

	bool m_NoTextures;
	
public:
	Mesh(const Geometry& geometry, const Material& material);
	Mesh(const Geometry& geometry, const std::vector<Texture>& textures);
	~Mesh();
	
	void Draw(const Camera& camera, const Shader& shader) const;
	void Destroy();

	glm::mat4 GetTransform() const;

private:
	void SetUpVertexArray(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void SetUpMaterial(const Material& material);
	void SetUpTextures(const std::vector<Texture>& textures);
};