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


	std::vector<float> light_vertices = {
		//	 px	   py	pz  
			-0.1, -0.1, 0.0,
			 0.1,  0.1, 0.0,
			 0.1, -0.1, 0.0,
			-0.1,  0.1, 0.0
	};

	std::vector<float> square_vertices = {
		//	 px	   py	pz   r	  g	   b	u	  v   nx   ny   nz
			-0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 0.0,  0.0, 0.0, 0.0, -1.0,
			 0.5,  0.5, 0.0, 1.0, 1.0, 1.0, 10.0, 10.0, 0.0, 0.0, -1.0,
			 0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 0.0,  10.0, 0.0, 0.0, -1.0,
			-0.5,  0.5, 0.0, 1.0, 1.0, 1.0, 10.0, 0.0, 0.0, 0.0, -1.0
	};

	std::vector<unsigned int> square_indices = { 0, 1, 2, 1, 3, 0 };


	std::vector<float> pyramid_vertices =
	{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	// Indices for vertices order
	std::vector<unsigned int> pyramid_indices =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	Shader defaultProgram = Shader("Resources/Shaders/default.vs", "Resources/Shaders/default.fs");
	Shader lightingProgram = Shader("Resources/Shaders/light.vs", "Resources/Shaders/light.fs");

	Mesh cube = Mesh(pyramid_vertices, pyramid_indices, "Resources/Images/brick.png", defaultProgram);
	Mesh floor = Mesh(square_vertices, square_indices, "Resources/Images/wall.jpg", defaultProgram);
	floor.EulerRotation.x = 3.14 / 2;
	floor.Position.y = -0.25;
	floor.Scale = glm::vec3(10.0f);
	LightSource light = LightSource(light_vertices, square_indices, glm::vec3(1.0f, 1.0f, 1.0f), lightingProgram);
	light.Position = glm::vec3(0.0f, 0.5f, 0.0f);
	Camera camera = Camera(_WIDTH, _HEIGHT, glm::vec3(0.0f, 1.0f, 4.0f));

	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow(), camera);
		
		// Rendering commands
		renderer.Clear();
		
		// Change object properties
		cube.EulerRotation.y = (float)glfwGetTime();
		cube.Position.y = cos(glfwGetTime())/2 + 0.5;
		light.Position.x = 2 * cos(2*glfwGetTime());
		light.Position.z = 2 * sin(2 * glfwGetTime());
		light.SetColor(glm::vec3(fabs(cos(glfwGetTime())), fabs(sin(glfwGetTime() / 2)), fabs(cos(glfwGetTime()) / 2)));
		
		// Render meshes
		renderer.Draw(floor, camera, light);
		renderer.Draw(cube, camera, light);
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