#include "Renderer.h"


#define BREAK __debugbreak();

Renderer::Renderer()
{
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	m_Program = Shader("Resources/Shaders/basic.vs", "Resources/Shaders/basic.fs");

	// Enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLErrorMessageCallback, 0);
}

Renderer::~Renderer()
{
	Shutdown();
	delete VAO;
	delete VBO;
	delete IBO;
}

void Renderer::Init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	float vertices[] = {
	//	 px	   py	pz   r	  g	   b
		-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
		 0.5,  0.5, 0.0, 0.0, 1.0, 0.0,
		 0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
		-0.5,  0.5, 0.0, 1.0, 0.0, 1.0
	};

	unsigned int indices[] = {0, 1, 2, 1, 3, 0};

	VAO = new VertexArray();
	
	VBO = new VertexBuffer();
	VBO->Bind();
	VBO->UploadData(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3); // Position attribute
	layout.Push<float>(3); // Color Attribute
	VAO->AttachVertexBuffer(*VBO, layout);

	IBO = new IndexBuffer();
	IBO->UploadData(indices, 6);
	IBO->Bind();
}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_Program.Bind();
	
	float time = glfwGetTime();
	float yVal = sin(time)/3;
	
	std::vector<float> mod = {
		cos(time) / 2.0f + 0.5f, 
		cos(time) / 2.0f + 0.5f,
		sin(time) / 2.0f + 0.5f,
	};
	
	m_Program.SetFloats("yPos", std::vector<float>{yVal});
	m_Program.SetFloats("ColorModifier", mod);
	
	VAO->Bind();
	IBO->Bind();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Shutdown()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_Program.Delete();
}

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;
	std::cerr << "------------ opengl error callback ------------" << std::endl;
	std::cout << "message: " << message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: " << id << std::endl;
	std::cout << "severity: ";
	switch (severity) {
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "LOG";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	}
	std::cout << std::endl;
	BREAK
}