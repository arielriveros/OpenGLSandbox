#include "Editor.h"

void AxisWidget(std::string name, std::string label, float* x, float* y, float* z, float speed)
{
	ImGui::PushItemWidth(100);
	ImGui::Text(label.c_str());
	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(50);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::ImColor(1.0f, 0.5f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::ImColor(1.0f, 0.25f, 0.25f, 1.0f));
	ImGui::DragFloat(("##" + name + label + "X").c_str(), x, speed);
	ImGui::PopStyleColor(2);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(50);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::ImColor(0.5f, 1.0f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::ImColor(0.25f, 1.0f, 0.25f, 1.0f));
	ImGui::DragFloat(("##" + name + label + "Y").c_str(), y, speed);
	ImGui::PopStyleColor(2);

	ImGui::SameLine(0.0f, 0.0f);
	ImGui::PushItemWidth(50);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::ImColor(0.5f, 0.5f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::ImColor(0.25f, 0.25f, 1.00f, 1.0f));
	ImGui::DragFloat(("##" + name + label + "Z").c_str(), z, speed);
	ImGui::PopStyleColor(2);
}