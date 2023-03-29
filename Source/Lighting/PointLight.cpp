#include "PointLight.h"
#include <glm/glm.hpp>

PointLight::PointLight(glm::vec3 color)
{
	Diffuse = color;
	Specular = color;

	m_Icon = new Sprite("Resources/Images/Icons", "light_icon.png");
}

PointLight::~PointLight()
{
	delete m_Icon;
}

void PointLight::Draw(const Camera& camera, const Shader& shader) const
{
	m_Icon->Position.x = this->Position.x;
	m_Icon->Position.y = this->Position.y;
	m_Icon->Position.z = this->Position.z;
	m_Icon->Color = this->Diffuse;
	m_Icon->Draw(camera, shader);
}

glm::mat4 PointLight::GetTransform() const
{
	const glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), Position);

	return transMatrix;
}
