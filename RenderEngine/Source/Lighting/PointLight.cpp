#include "PointLight.h"
#include <glm/glm.hpp>
#include <imgui.h>

PointLight::PointLight(std::string name, glm::vec3 color): Light(name, color)
{
	
}

PointLight::~PointLight()
{
}

void PointLight::OnGui()
{
	Light::OnGui();

	ImGui::PushItemWidth(80);
	ImGui::DragFloat(("Constant ##" + Name).c_str(), (float*)& Constant, 0.01f, 0.01f);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(("Linear ##" + Name).c_str(), (float*)&Linear, 0.01f, 0.001f);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(("Quadratic ##" + Name).c_str(), (float*)&Quadratic, 0.01f, 0.0001f);
}
