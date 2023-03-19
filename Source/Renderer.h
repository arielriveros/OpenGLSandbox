#pragma once
#include "Window.h"
#include "Shader.h"

class Renderer
{
private:
	Shader m_Program;
	
public:
	Renderer();

	void Init();
	void Render();

};

