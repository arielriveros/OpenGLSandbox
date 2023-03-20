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

	std::vector<float> vector_vertices2 = {
		//	 px	   py	pz   r	  g	   b	  u	  v
			-0.9, -0.9, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
			 0.1,  0.1, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
			 0.1, -0.9, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
			-0.9,  0.1, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0
	};
	
	std::vector<unsigned int> vector_indices = { 0, 1, 2, 1, 3, 0 };
	Shader basicProgram = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	Shader texturedProgram = Shader("Resources/Shaders/textured.vs", "Resources/Shaders/textured.fs");
	Texture texture = Texture("Resources/Images/wall.jpg");
	Mesh mesh = Mesh(vector_vertices, vector_indices, texture, basicProgram);
	Mesh mesh2 = Mesh(vector_vertices2, vector_indices, texture, texturedProgram);
	
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

		basicProgram.SetFloats("yPos", {yVal});
		texturedProgram.SetFloats("u_ColorModifier", mod);
		renderer.Clear();
		renderer.Draw(mesh);
        renderer.Draw(mesh2);
        
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