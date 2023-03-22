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

class Renderer
{
private:
	Shader m_defaultProgram;
	Shader m_iconProgram;
public:
	Renderer();
	~Renderer();

	void Init();
	void Clear() const;
	void Draw(const Mesh& mesh, const Camera& camera, const PointLight& light) const;
	void Draw(const PointLight& light, const Camera& camera) const;
	void Shutdown();

};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);