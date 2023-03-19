#include "Renderer.h"

Renderer::Renderer()
{
	m_Program = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
}

void Renderer::Init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	float vertices[9] = {
		-0.5, -0.5, 0.0,
		 0.0,  0.5, 0.0,
		 0.5, -0.5, 0.0
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_Program.Bind();
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}