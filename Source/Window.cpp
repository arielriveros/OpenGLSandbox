#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	// Init GLFW
	glfwInit();
	// OpenGL Version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Antialiasing
	glfwWindowHint(GLFW_SAMPLES, 8);

	m_Title = title;
	m_Height = height;
	m_Width = width;

	// Initialize Window
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	
}

Window::~Window()
{
}

void Window::Update()
{
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::OnResize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


bool Window::Init()
{
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window); // Makes the created window the openGL context to work with
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(m_Window, OnResize_callback);

	// Initializes openGL functions with glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, m_Width, m_Height);
	return true;
}

void Window::Destroy()
{
	// Cleanup after stopping glfw
	glfwTerminate();
}

void Window::SwapBuffersAndPollEvents()
{
	// Event polling and buffer swapping
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

