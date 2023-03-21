#include <imgui/imgui.h>
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Mesh/Mesh.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Lighting/LightSource.h"

const unsigned int _WIDTH = 800;
const unsigned int _HEIGHT = 600;

void processInput(GLFWwindow* window, Camera& camera);
bool firstMouse = true;
float lastX = _WIDTH / 2.0;
float lastY = _HEIGHT / 2.0;

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

	std::vector<float> light_vertices = {
		//	 px	   py	pz  
			-0.5, -0.5, 0.0,
			 0.5,  0.5, 0.0,
			 0.5, -0.5, 0.0,
			-0.5,  0.5, 0.0
	};

	std::vector<float> square_vertices = {
		//	 px	   py	pz   r	  g	   b	  u	  v
			-0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0,
			 0.5,  0.5, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
			 0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0,
			-0.5,  0.5, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0
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
	Shader lightingProgram = Shader("Resources/Shaders/light.vs", "Resources/Shaders/light.fs");

	Mesh pyramid = Mesh(pyramid_vertices, pyramid_indices, "Resources/Images/brick.png", texturedProgram);
	Mesh square = Mesh(square_vertices, square_indices, "Resources/Images/wall.jpg", texturedProgram);
	LightSource light = LightSource(light_vertices, square_indices, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), lightingProgram);
	Camera camera = Camera(_WIDTH, _HEIGHT, glm::vec3(0.0f, 0.0f, 1.0f));

	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow(), camera);
		
		// Rendering commands
		renderer.Clear();		

		glm::mat4 squareTransform = glm::mat4(1.0f);
		squareTransform = glm::translate(squareTransform, glm::vec3(0.0f, -1.0f, 0.0f));
		squareTransform = glm::rotate(squareTransform, (float) 3.14 / 2, glm::vec3(1.0f, 0.0f, 0.0f));
		squareTransform = glm::scale(squareTransform, glm::vec3(10.0));
		square.SetTransform(squareTransform);
		renderer.Draw(square, camera, light);
		
		glm::mat4 pyramidTransform = glm::mat4(1.0f);
		pyramidTransform = glm::translate( pyramidTransform, glm::vec3( 0.0f, cos(glfwGetTime())/3.0f - 0.33f, 0.0f) );
		pyramidTransform = glm::rotate(pyramidTransform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		pyramid.SetTransform(pyramidTransform);
		renderer.Draw(pyramid, camera, light);
        
		glm::mat4 lightTransform = glm::mat4(1.0f);
		lightTransform = glm::translate(lightTransform, glm::vec3(1.0f, 0.5f, -1.0f));
		light.SetTransform(lightTransform);
		light.SetColor(glm::vec4(fabs(cos(glfwGetTime())), 1.0f, 1.0f, 1.0f));
		renderer.Draw(light, camera);


        window.SwapBuffersAndPollEvents();
    }
	
	// Cleanup after stopping loop
    renderer.Shutdown();
    window.Destroy();
    return 0;
}

// Process Input from keyboard
void processInput(GLFWwindow* window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX, mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float xpos = static_cast<float>(mouseX);
		float ypos = static_cast<float>(mouseY);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		camera.Rotate(xoffset, yoffset);
		
		lastX = xpos;
		lastY = ypos;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstMouse = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.Position += camera.speed * camera.Forward;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.Position += camera.speed * (-camera.Forward);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Position += camera.speed * (-camera.Right);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.Position += camera.speed * camera.Right;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.Position += camera.speed * camera.Up;

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.Position += camera.speed * (-camera.Up);


}