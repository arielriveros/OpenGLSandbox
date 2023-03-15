#include <imgui/imgui.h>
#include <iostream>
#include "./Window.h"

const unsigned int _WIDTH = 800;
const unsigned int _HEIGHT = 600;

void framebufferResize_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    Window window = Window(_WIDTH, _HEIGHT, "Sandbox");
    if (!window.Init())
        return -1;

	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow());
		
		// Rendering commands
		
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        window.SwapBuffersAndPollEvents();
    }
	
	// Cleanup after stopping glfw
    //glfwTerminate();
    window.Destroy();
    return 0;
}

//Callback for windows resize.
void framebufferResize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Process Input from keyboard
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}