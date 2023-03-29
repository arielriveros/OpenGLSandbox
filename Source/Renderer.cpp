#include "Renderer.h"
#include <string>


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
	// Enable Depth testing
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Cull
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	// Enable MSAA
	glEnable(GL_MULTISAMPLE);

	m_defaultProgram = Shader("Source/Shader/Sources/default.vs", "Source/Shader/Sources/default.fs");
	m_iconProgram = Shader("Source/Shader/Sources/icon.vs", "Source/Shader/Sources/icon.fs");
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Mesh& mesh, const Camera& camera) const
{
	SetLights();
	mesh.Draw(camera, m_defaultProgram);
}

void Renderer::DrawLights(const Camera& camera) const
{
	if(m_DirectionalLight)
		m_DirectionalLight->Draw(camera, m_iconProgram);

	for (const PointLight* pointLight : m_PointLights)
	{
		pointLight->Draw(camera, m_iconProgram);
	}
}

void Renderer::AddPointLight(const PointLight& pointLight)
{
	m_PointLights.push_back(&pointLight);
}

void Renderer::AddDirectionalLight(const DirectionalLight& directionalLight)
{
	m_DirectionalLight = &directionalLight;
}


void Renderer::Shutdown()
{
	
}

void Renderer::SetLights() const
{
	if (m_DirectionalLight)
	{
		m_defaultProgram.SetVec3("u_directionalLight.direction", m_DirectionalLight->Direction);
		m_defaultProgram.SetVec3("u_directionalLight.diffuse", m_DirectionalLight->Diffuse);
		m_defaultProgram.SetVec3("u_directionalLight.ambient", m_DirectionalLight->Ambient);
		m_defaultProgram.SetVec3("u_directionalLight.specular", m_DirectionalLight->Specular);
	}

	unsigned int pointLightsCount = static_cast<unsigned int>(m_PointLights.size());
	m_defaultProgram.SetInt("u_pointLightsCount", pointLightsCount );

	for (unsigned int i = 0; i < pointLightsCount; i++)
	{
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].position", m_PointLights[i]->Position);
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].diffuse", m_PointLights[i]->Diffuse);
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].ambient", m_PointLights[i]->Ambient);
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].specular", m_PointLights[i]->Specular);

		m_defaultProgram.SetFloat("u_pointLights[" + std::to_string(i) + "].constant", m_PointLights[i]->Constant );
		m_defaultProgram.SetFloat("u_pointLights[" + std::to_string(i) + "].linear", m_PointLights[i]->Linear );
		m_defaultProgram.SetFloat("u_pointLights[" + std::to_string(i) + "].quadratic", m_PointLights[i]->Quadratic );
	}
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
		BREAK
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		BREAK
		break;
	}
	std::cout << std::endl;
}