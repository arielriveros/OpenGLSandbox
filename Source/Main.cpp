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

	float vertices[] = {
		//	 px	   py	pz   r	  g	   b	  u	  v
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
			 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0
	};

	unsigned int indices[] = { 0, 1, 2, 1, 3, 0 };

	VertexArray VAO = VertexArray();

	VertexBuffer VBO = VertexBuffer();
	VBO.UploadData(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	layout.Push<float>(2); // UV Attribute
	VAO.AttachVertexBuffer(VBO, layout);

	IndexBuffer IBO = IndexBuffer();
	IBO.UploadData(indices, 6);

	Shader shaderProgram = Shader("Resources/Shaders/textured.vs", "Resources/Shaders/textured.fs");

	Texture texture = Texture("Resources/Images/wall.jpg");
	texture.Bind();
	shaderProgram.SetInts("u_Texture", {0});
	
	shaderProgram.Unbind();
	VBO.Unbind();
	IBO.Unbind();
	
	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow());
		
		// Rendering commands
		float time = glfwGetTime();
		float yVal = sin(time) / 3;

		std::vector<float> mod = {
			cos(time) / 2.0f + 0.5f,
			cos(time) / 2.0f + 0.5f,
			sin(time) / 2.0f + 0.5f,
		};

		shaderProgram.SetFloats("yPos", {yVal});
		shaderProgram.SetFloats("u_ColorModifier", mod);
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