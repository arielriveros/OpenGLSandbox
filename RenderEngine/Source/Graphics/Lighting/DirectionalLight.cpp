#include "DirectionalLight.h"
#include <imgui.h>

DirectionalLight::DirectionalLight(std::string name, glm::vec3 color): Light(name, color)
{

}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::OnGui()
{
	Light::OnGui();
}
