#include "Scene.h"
#include <imgui/imgui.h>

Scene::Scene()
{
	m_MeshRoot = Mesh("Scene");
	m_DirectionalLight = nullptr;
}

Scene::~Scene()
{
}

void Scene::AddChild(Mesh* mesh)
{
	m_MeshRoot.AddChild(mesh);
}

void Scene::AddChild(DirectionalLight* directionalLight)
{
	m_DirectionalLight = directionalLight;
}

void Scene::AddChild(PointLight* pointLight)
{
	m_PointLights.push_back(pointLight);
}

void Scene::Update()
{
	m_MeshRoot.Update();
}

void Scene::OnGui()
{
	if (ImGui::CollapsingHeader("Lighting"))
	{
		m_DirectionalLight->OnGui();
		for (PointLight* pointLight : m_PointLights)
			pointLight->OnGui();
	}
	
	if (ImGui::CollapsingHeader("Meshes"))
		m_MeshRoot.OnGui();
}
