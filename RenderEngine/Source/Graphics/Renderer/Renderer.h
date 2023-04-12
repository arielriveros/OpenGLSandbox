#pragma once

#include "../Shader/Shader.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/IndexBuffer.h"
#include "../Buffers/Framebuffer.h"
#include "../VertexArray/VertexArray.h"
#include "../Texture/Texture.h"
#include "../Mesh/Mesh.h"
#include "../Lighting/PointLight.h"
#include "../Lighting/DirectionalLight.h"
#include "../PostProcess/PostProcess.h"
#include "../../Camera/Camera.h"
#include "../../Scene/Scene.h"
#include "../../Window/Window.h"
#include <vector>

class Renderer
{
public:
	float Gamma = 2.2f;
	bool ShowLights = false;
private:
	Shader m_defaultProgram, m_iconProgram, m_postProcessProgram, m_shadowMapProgram;
	PostProcess m_PostProcess;
	
	Framebuffer m_ShadowMapFBO;
	unsigned int m_DepthMap;
	unsigned int m_ShadowResolution;

public:
	Renderer();
	~Renderer();

	void Init();
	void Clear() const;
	void Draw(const Scene& scene, const Camera& camera) const;
	void Shutdown();

private:
	void SetLights(DirectionalLight* directionalLight, std::vector<PointLight*> pointLights) const;
	void DrawLights(DirectionalLight* directionalLight, std::vector<PointLight*> pointLights, const Camera& camera) const;
	void Draw(const Mesh& mesh, const Camera& camera) const;
};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);