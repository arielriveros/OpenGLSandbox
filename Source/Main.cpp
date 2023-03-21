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


	 
	std::vector<float> triangle_vertices = {
		//	 px	   py	pz   r	  g	   b
			-0.25,  0.0, 0.0, 1.0, 0.0, 0.0,
			 0.25,  0.0, 0.0, 0.0, 1.0, 0.0,
			 0.0,  0.5, 0.0, 1.0, 0.0, 1.0
	};

	std::vector<float> square_vertices = {
		//	 px	   py	pz   r	  g	   b	  u	  v
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
			 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0
	};

	std::vector<unsigned int> square_indices = { 0, 1, 2, 1, 3, 0 };

	std::vector<float> pyramid_vertices = {
		//	 px	   py	  pz    r	  g		b	  u    v
			-0.5f, 0.0f,  0.5f, 0.83, 0.70, 0.44, 0.0, 0.0,
			-0.5f, 0.0f, -0.5f, 0.83, 0.70, 0.44, 1.0, 0.0,
			 0.5f, 0.0f, -0.5f, 0.83, 0.70, 0.44, 0.0, 0.0,
			 0.5f, 0.0f,  0.5f, 0.83, 0.70, 0.44, 1.0, 0.0,
			 0.0f, 0.8f,  0.0f, 0.92, 0.86, 0.76, 0.5, 1.0
	};
	
	std::vector<unsigned int> pyramid_indices = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	Shader basicProgram = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");
	Shader texturedProgram = Shader("Resources/Shaders/textured.vs", "Resources/Shaders/textured.fs");

	Mesh triangle = Mesh(triangle_vertices, {0, 1, 2}, basicProgram);
	Mesh pyramid = Mesh(pyramid_vertices, pyramid_indices, "Resources/Images/brick.png", texturedProgram);
	Mesh square = Mesh(square_vertices, square_indices, "Resources/Images/wall.jpg", texturedProgram);
	
	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow());
		
		// Rendering commands
		renderer.Clear();

		// Model View Projection
		glm::mat4 view(1.0f);
		glm::mat4 proj(1.0f);

		view = glm::translate(view, glm::vec3(0.0f,0.0f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(_WIDTH / _HEIGHT), 0.1f, 100.0f);

		basicProgram.SetMat4("u_proj", proj);
		basicProgram.SetMat4("u_view", view);

		texturedProgram.SetMat4("u_proj", proj);
		texturedProgram.SetMat4("u_view", view);
		

		glm::mat4 transform1 = glm::mat4(1.0f);
		transform1 = glm::translate(transform1, glm::vec3(0.5f, -0.5f, 0.0f));
		transform1 = glm::rotate(transform1, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		triangle.SetTransform(transform1);
		renderer.Draw(triangle);
		
		glm::mat4 transform2 = glm::mat4(1.0f);
		transform2 = glm::translate(transform2, glm::vec3(0.0f, 0.25f, 0.0f));
		transform2 = glm::scale(transform2, glm::vec3(0.75f));
		square.SetTransform(transform2);
        renderer.Draw(square);
		
		glm::mat4 transform3 = glm::mat4(1.0f);
		transform3 = glm::translate( transform3, glm::vec3( 0.0f, cos(glfwGetTime())/3.0f - 0.33f, 0.0f) );
		transform3 = glm::rotate(transform3, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		pyramid.SetTransform(transform3);
		renderer.Draw(pyramid);
        
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