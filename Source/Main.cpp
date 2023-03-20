#include <imgui/imgui.h>
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Mesh/Mesh.h"

const unsigned int _WIDTH = 600;
const unsigned int _HEIGHT = 600;

void processInput(GLFWwindow* window);

int main()
{
	// Window context setup
    Window window = Window(_WIDTH, _HEIGHT, "Sandbox");
    if (!window.Init())
        return -1;

    Renderer renderer = Renderer();
    renderer.Init();


	 
	std::vector<float> vector_vertices = {
		//	 px	   py	pz   r	  g	   b	  u	  v
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
			 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0
	};
	
	std::vector<unsigned int> vector_indices = { 0, 1, 2, 1, 3, 0 };
	Shader shaderProgram = Shader("Resources/Shaders/textured.vs", "Resources/Shaders/textured.fs");
	Texture texture = Texture("Resources/Images/wall.jpg");
	Mesh mesh = Mesh(vector_vertices, vector_indices, texture, shaderProgram);
	
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
		//renderer.Draw(VAO, IBO, shaderProgram);
        renderer.Draw(mesh);
        
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