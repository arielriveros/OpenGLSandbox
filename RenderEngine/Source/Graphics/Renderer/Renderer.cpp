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
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Enable MSAA
	glEnable(GL_MULTISAMPLE);

	m_defaultProgram = Shader("Resources/Shaders/default.vs", "Resources/Shaders/default.fs");
	m_defaultProgram.Bind();
	m_iconProgram = Shader("Resources/Shaders/icon.vs", "Resources/Shaders/icon.fs");
	m_postProcessProgram = Shader("Resources/Shaders/postProcess.vs", "Resources/Shaders/postProcess.fs");
	m_shadowMapProgram = Shader("Resources/Shaders/shadowMap.vs", "Resources/Shaders/shadowMap.fs");

	// Post Process
	m_PostProcess = PostProcess(1280, 720, &m_postProcessProgram); // TODO: Change resolution dynamically
	m_PostProcess.Init();

	// Shadow mapping
	m_shadowMapProgram.Bind();
	m_ShadowResolution = 4096;
	m_ShadowMapFBO = Framebuffer(m_ShadowResolution, m_ShadowResolution);

	m_ShadowMapFBO.Bind();
	m_ShadowMapFBO.AttachDepth();
	m_ShadowMapFBO.CheckCompletion();
	m_ShadowMapFBO.Unbind();
}

void Renderer::Clear() const
{
	m_PostProcess.Clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Mesh& mesh,const Camera& camera) const
{
	glViewport(0, 0, 1280, 720);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_PostProcess.Bind();
	glActiveTexture(GL_TEXTURE0 + 4);
	glBindTexture(GL_TEXTURE_2D, m_ShadowMapFBO.GetDepthBufferID());
	mesh.Draw(camera, m_defaultProgram);
	m_PostProcess.Unbind();

	m_PostProcess.Draw();
}

void Renderer::DrawLights(DirectionalLight* directionalLight, std::vector<PointLight*> pointLights, const Camera& camera) const
{
	if(directionalLight)
		directionalLight->Draw(camera, m_iconProgram);

	for (const PointLight* pointLight : pointLights)
	{
		pointLight->Draw(camera, m_iconProgram);
	}
}

void Renderer::Draw(const Scene& scene, const Camera& camera) const
{
	glViewport(0, 0, m_ShadowResolution, m_ShadowResolution);
	m_ShadowMapFBO.Bind();
	glClear(GL_DEPTH_BUFFER_BIT);

	if (scene.GetDirectionalLight())
	{
		m_defaultProgram.Bind();
		m_defaultProgram.SetMat4("u_lightSpaceMatrix", scene.GetDirectionalLight()->GetViewProjection());
		m_defaultProgram.SetInt("shadowMap", 4);

		m_shadowMapProgram.Bind();
		m_shadowMapProgram.SetMat4("u_lightSpaceMatrix", scene.GetDirectionalLight()->GetViewProjection());
		glDisable(GL_CULL_FACE);
		scene.GetRoot().Draw(camera, m_shadowMapProgram);
		glEnable(GL_CULL_FACE);
		m_shadowMapProgram.Unbind();
	}
	m_ShadowMapFBO.Unbind();

	SetLights(scene.GetDirectionalLight(), scene.GetPointLights());
	Draw(scene.GetRoot(), camera);
	if (ShowLights)
		DrawLights(scene.GetDirectionalLight(), scene.GetPointLights(), camera);
}


void Renderer::Shutdown()
{
	
}

void Renderer::SetLights(DirectionalLight* directionalLight, std::vector<PointLight*> pointLights) const
{
	m_defaultProgram.Bind();
	if (directionalLight)
	{
		m_defaultProgram.SetVec3("u_directionalLight.position", directionalLight->Position);
		m_defaultProgram.SetVec3("u_directionalLight.target", glm::vec3(0.0f, 0.0f, 0.0f));
		m_defaultProgram.SetVec3("u_directionalLight.diffuse", directionalLight->Diffuse);
		m_defaultProgram.SetVec3("u_directionalLight.ambient", directionalLight->Ambient);
		m_defaultProgram.SetVec3("u_directionalLight.specular", directionalLight->Specular);
	}

	unsigned int pointLightsCount = static_cast<unsigned int>(pointLights.size());
	m_defaultProgram.SetInt("u_pointLightsCount", pointLightsCount );

	for (unsigned int i = 0; i < pointLightsCount; i++)
	{
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].position", pointLights[i]->Position);
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].diffuse", pointLights[i]->Diffuse);
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].ambient", pointLights[i]->Ambient);
		m_defaultProgram.SetVec3("u_pointLights[" + std::to_string(i) + "].specular", pointLights[i]->Specular);

		m_defaultProgram.SetFloat("u_pointLights[" + std::to_string(i) + "].constant", pointLights[i]->Constant );
		m_defaultProgram.SetFloat("u_pointLights[" + std::to_string(i) + "].linear", pointLights[i]->Linear );
		m_defaultProgram.SetFloat("u_pointLights[" + std::to_string(i) + "].quadratic", pointLights[i]->Quadratic );
	}

	m_defaultProgram.SetFloat("u_gamma", Gamma);
	m_defaultProgram.Unbind();
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