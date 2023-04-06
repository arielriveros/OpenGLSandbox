#include "Light.h"
#include <imgui.h>

Light::Light(std::string name, glm::vec3 color)
{
	Name = name;

	Diffuse = color;
	Specular = color;
	Ambient = color / 2.0f;

	m_Icon = new Sprite("Resources/Images/Icons", "light_icon.png");
}

Light::~Light()
{
	delete m_Icon;
}

void Light::Draw(const Camera& camera, const Shader& shader) const
{
	m_Icon->Position.x = this->Position.x;
	m_Icon->Position.y = this->Position.y;
	m_Icon->Position.z = this->Position.z;
	m_Icon->Color = this->Diffuse;
	m_Icon->Draw(camera, shader);
}

void Light::OnGui()
{
	ImGui::PushItemWidth(100);
	ImGui::Text(Name.c_str());

	ImGui::Text("Diffuse");
	ImGui::SameLine(0.0f, 0.0f);
	ImGui::ColorEdit3(("##" + Name + "Diffuse").c_str(), (float*)&Diffuse, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::Text("Specular");
	ImGui::SameLine(0.0f, 0.0f);
	ImGui::ColorEdit3(("##" + Name + "Specular").c_str(), (float*)&Specular, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::Text("Ambient");
	ImGui::SameLine(0.0f, 0.0f);
	ImGui::ColorEdit3(("##" + Name + "Ambient").c_str(), (float*)&Ambient, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

	ImGui::PushItemWidth(100);
	ImGui::Text("Position");

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(50);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::ImColor(1.0f, 0.5f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::ImColor(1.0f, 0.25f, 0.25f, 1.0f));
	ImGui::DragFloat(("##" + Name + "PosX").c_str(), (float*)&Position.x, 0.01f);
	ImGui::PopStyleColor(2);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(50);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::ImColor(0.5f, 1.0f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::ImColor(0.25f, 1.0f, 0.25f, 1.0f));
	ImGui::DragFloat(("##" + Name + "PosY").c_str(), (float*)&Position.y, 0.01f);
	ImGui::PopStyleColor(2);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(50);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::ImColor(0.5f, 0.5f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::ImColor(0.25f, 0.25f, 1.00f, 1.0f));
	ImGui::DragFloat(("##" + Name + "PosZ").c_str(), (float*)&Position.z, 0.01f);
	ImGui::PopStyleColor(2);
}

glm::mat4 Light::GetTransform() const
{
	const glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), Position);

	return transMatrix;
}
