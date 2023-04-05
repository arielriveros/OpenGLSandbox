#include "PointLight.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>

PointLight::PointLight(std::string name, glm::vec3 color): Light(name, color)
{
	
}

PointLight::~PointLight()
{
}

void PointLight::OnGui()
{
	Light::OnGui();
}
