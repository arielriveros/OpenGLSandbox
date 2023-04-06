#include "Window.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::OnResize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


bool Window::Init(GLFWframebuffersizefun callback)
{
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window); // Makes the created window the openGL context to work with
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(m_Window, callback);

	// Initializes openGL functions with glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	glViewport(0, 0, m_Width, m_Height);
	return true;
}

void Window::Destroy()
{
	// Cleanup after stopping glfw
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

}

void Window::PostUpdate()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Event polling and buffer swapping
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

