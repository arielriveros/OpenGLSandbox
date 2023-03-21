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


	 
	std::vector<float> square_vertices = {
		//	 px	   py	pz   r	  g	   b
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
			 0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 0.0, 1.0
	};

	std::vector<float> square_uv_vertices = {
		//	 px	   py	pz   r	  g	   b	  u	  v
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
			 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0
	};
	std::vector<unsigned int> square_indices = { 0, 1, 2, 1, 3, 0 };

	Shader basicProgram = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	Shader texturedProgram = Shader("Resources/Shaders/textured.vs", "Resources/Shaders/textured.fs");

	Mesh mesh1 = Mesh(square_vertices, square_indices, basicProgram);
	Mesh mesh2 = Mesh(square_uv_vertices, square_indices, "Resources/Images/brick.png", texturedProgram);
	Mesh mesh3 = Mesh(square_uv_vertices, square_indices, "Resources/Images/wall.jpg", texturedProgram);
	
	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow());
		
		// Rendering commands
		glm::mat4 transform1 = glm::mat4(1.0f);
		glm::mat4 transform2 = glm::mat4(1.0f);
		glm::mat4 transform3 = glm::mat4(1.0f);
		
		renderer.Clear();

		transform1 = glm::rotate(transform1, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		transform1 = glm::translate(transform1, glm::vec3(0.5f, -0.5f, 0.0f));
		mesh1.SetTransform(transform1);
		renderer.Draw(mesh1);
		
		transform2 = glm::translate(transform2, glm::vec3(-0.5f, 0.5f, 0.0f));
		transform2 = glm::scale(transform2, glm::vec3(0.5f));
		mesh3.SetTransform(transform2);
        renderer.Draw(mesh2);
		
		transform3 = glm::translate(
			transform3, 
			glm::vec3(
				0.5f, 
				0.5f, 
				cos(glfwGetTime()
			)
		));
		transform3 = glm::rotate(transform3, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		//mesh3.SetTransform(transform3);
		renderer.Draw(mesh3);
        
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