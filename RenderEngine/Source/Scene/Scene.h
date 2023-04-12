#pragma once
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Lighting/DirectionalLight.h"
#include "../Graphics/Lighting/PointLight.h"
#include <vector>

class Scene
{
private:
	Mesh m_MeshRoot;
	std::vector<PointLight*> m_PointLights;
	DirectionalLight* m_DirectionalLight;

public:
	Scene();
	~Scene();
	void AddChild(Mesh* mesh);
	void AddChild(DirectionalLight* directionalLight);
	void AddChild(PointLight* pointLight);
	void Update();
	void OnGui();

	Mesh GetRoot() const { return m_MeshRoot; }
	std::vector<PointLight*> GetPointLights() const{ return m_PointLights; }
	DirectionalLight* GetDirectionalLight() const { return m_DirectionalLight; }
};