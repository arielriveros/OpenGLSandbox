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
	//	 px	   py	pz   r	  g	   b
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
		 0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
		 0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
		-0.5,  0.5, 0.0, 1.0, 0.0, 1.0
	};

	unsigned int indices[] = {0, 1, 2, 1, 3, 0};

	unsigned int VBO, VAO, IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_Program.Bind();
	
	float time = glfwGetTime();
	float yVal = sin(time)/3;
	
	std::vector<float> mod = {
		cos(time) / 2.0f + 0.5f, 
		cos(time) / 2.0f + 0.5f,
		sin(time) / 2.0f + 0.5f,
	};
	
	m_Program.SetFloats("yPos", std::vector<float>{yVal});
	m_Program.SetFloats("ColorModifier", mod);
	
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Shutdown()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_Program.Delete();
}