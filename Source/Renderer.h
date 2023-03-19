#pragma once
#include "Window.h"
#include "Shader.h"

class Renderer
{
private:
	Shader m_Program;
	
public:
	Renderer();
	~Renderer();

	void Init();
	void Render();
	void Shutdown();

};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);