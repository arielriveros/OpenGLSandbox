#pragma once
#include "Window.h"
#include "Shader/Shader.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "VertexArray/VertexArray.h"

class Renderer
{
private:
	Shader m_Program;
	VertexArray* VAO = nullptr;
	VertexBuffer* VBO = nullptr;
	IndexBuffer* IBO = nullptr;
	
public:
	Renderer();
	~Renderer();

	void Init();
	void Render();
	void Shutdown();

};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);