#include "Renderer.h"

Renderer::Renderer()
{
	m_Program = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
}

Renderer::~Renderer()
{
	Shutdown();
}

void Renderer::Init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	float vertices[] = {
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
		 0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
		 0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
		
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
		 0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
		-0.5,  0.5, 0.0, 1.0, 0.0, 1.0
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_Program.Bind();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Shutdown()
{
	m_Program.Delete();
}