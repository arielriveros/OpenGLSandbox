#include <imgui/imgui.h>
#include <iostream>
#include "Window.h"
#include "Renderer.h"

const unsigned int _WIDTH = 640;
const unsigned int _HEIGHT = 480;

void processInput(GLFWwindow* window);

int main()
{
	// Window context setup
    Window window = Window(_WIDTH, _HEIGHT, "Sandbox");
    if (!window.Init())
        return -1;

    Renderer renderer = Renderer();
    renderer.Init();

    Shader shaderProgram = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");

	float vertices[] = {
		//	 px	   py	pz   r	  g	   b
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
			 0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 0.0, 1.0
	};

	unsigned int indices[] = { 0, 1, 2, 1, 3, 0 };

	VertexArray VAO = VertexArray();

	VertexBuffer VBO = VertexBuffer();
	VBO.Bind();
	VBO.UploadData(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	VAO.AttachVertexBuffer(VBO, layout);

	IndexBuffer IBO = IndexBuffer();
	IBO.UploadData(indices, 6);
	IBO.Bind();
	
	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow());
		
		// Rendering commands
		renderer.Clear();
        renderer.Draw(VAO, IBO, shaderProgram);
        
        window.SwapBuffersAndPollEvents();
    }
	
	// Cleanup after stopping loop
    renderer.Shutdown();
    window.Destroy();
    return 0;
}

// Process Input from keyboard
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}