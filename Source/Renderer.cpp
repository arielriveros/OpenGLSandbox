#include "Renderer.h"
#define BREAK __debugbreak();

Renderer::Renderer()
{
	std::cout << glGetString(GL_VERSION) << std::endl;
	// Enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLErrorMessageCallback, 0);
}

Renderer::~Renderer()
{
	Shutdown();
}

void Renderer::Init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.Bind();
	
	float time = glfwGetTime();
	float yVal = sin(time)/3;
	
	std::vector<float> mod = {
		cos(time) / 2.0f + 0.5f, 
		cos(time) / 2.0f + 0.5f,
		sin(time) / 2.0f + 0.5f,
	};
	
	shader.SetFloats("yPos", std::vector<float>{yVal});
	shader.SetFloats("ColorModifier", mod);
	
	vao.Bind();
	ibo.Bind();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Shutdown()
{
	
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