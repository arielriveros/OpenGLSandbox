#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	m_Icon = new Sprite("Resources/Images/Icons", "light_icon.png");
}

DirectionalLight::~DirectionalLight()
{
	delete m_Icon;
}

void DirectionalLight::Draw(const Camera& camera, const Shader& shader) const
{
	m_Icon->Position.x = this->Position.x;
	m_Icon->Position.y = this->Position.y;
	m_Icon->Position.z = this->Position.z;
	m_Icon->Color = this->Diffuse;
	m_Icon->Draw(camera, shader);
}