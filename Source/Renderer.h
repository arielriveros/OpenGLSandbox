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
#include "Buffers/Framebuffer.h"
#include "PostProcess/PostProcess.h"

class Renderer
{
public:
	float Gamma = 2.2f;
private:
	Shader m_defaultProgram, m_iconProgram, m_postProcessProgram;
	const DirectionalLight* m_DirectionalLight = nullptr;
	std::vector<const PointLight*> m_PointLights;
	PostProcess m_PostProcess;

public:
	Renderer();
	~Renderer();

	void Init();
	void Clear() const;
	void AddPointLight(const PointLight& pointLight);
	void AddDirectionalLight(const DirectionalLight& directionalLight);
	void Draw(const Mesh& mesh, const Camera& camera) const;
	void DrawLights(const Camera& camera) const;
	void Shutdown();

private:
	void SetLights() const;
};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);