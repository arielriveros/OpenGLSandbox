#pragma once
#include "Window.h"
#include "Shader/Shader.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "VertexArray/VertexArray.h"
#include "Texture/Texture.h"
#include "Mesh/Mesh.h"
#include "Camera/Camera.h"
#include "Lighting/PointLight.h"
#include "Lighting/DirectionalLight.h"
#include <vector>
#include "Model/Model.h"

class Renderer
{
private:
	Shader m_defaultProgram;
	Shader m_iconProgram;
	const DirectionalLight* m_DirectionalLight = nullptr;
	std::vector<const PointLight*> m_PointLights;

public:
	Renderer();
	~Renderer();

	void Init();
	void Clear() const;
	void AddPointLight(const PointLight& pointLight);
	void AddDirectionalLight(const DirectionalLight& directionalLight);
	void Draw(const Mesh& mesh, const Camera& camera) const;
	void Draw(const Model& model, const Camera& camera) const;
	void DrawLights(const Camera& camera) const;
	void Shutdown();

private:
	void SetLights() const;
};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);