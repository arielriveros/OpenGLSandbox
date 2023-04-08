#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "../Resources/Misc/Geometries.h"
#include "../Resources/Misc/Materials.h"
#include "Loaders/ModelLoader.h"
#include <imgui.h>
#include <iostream>
#include "Scene/Scene.h"



class RendererApplication
{
private:
	Window*		m_Window	= nullptr;
	Renderer*	m_Renderer	= nullptr;
	Scene*		m_Scene		= nullptr;
	Camera*		m_Camera	= nullptr;

	unsigned int m_Width= 1280;
	unsigned int m_Height = 720;

	bool m_FirstMouse = true;
	float m_LastX = m_Width / 2.0f;
	float m_LastY = m_Height / 2.0f;

public:
	RendererApplication(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
		// Window context setup
		m_Window = new Window(m_Width, m_Height, "Sandbox");
		if (!m_Window->Init(OnResize))
			std::cout << "Application Error" << std::endl;

		m_Renderer = new Renderer();
		m_Scene = new Scene();
	}

	~RendererApplication()
	{
	}

	void Init()
	{
		m_Renderer->Init();
		m_Renderer->ShowLights = true;

		m_Camera = new Camera(m_Width, m_Height, glm::vec3(0.0f, 1.5f, 3.5f));

		float offset = 2.0f;

		// Floor
		Mesh* floor = new Mesh("floor", squareGeometry, Materials::turquoise);
		floor->Rotation.x = -3.14f / 2;
		floor->Position.y = -0.5f;

		// Wall
		Texture brickwall_D("Resources/Images/Textures", "brickwall_albedo.jpg", "texture_diffuse");
		Texture brickwall_N("Resources/Images/Textures", "brickwall_normal.jpg", "texture_normal");
		Mesh* wall = new Mesh("wall", squareGeometry, { brickwall_D, brickwall_N });
		wall->Position.z = -0.5f;

		Mesh* groupMesh = new Mesh("Group");
		groupMesh->Position.y = 1.5f;
		groupMesh->Scale = glm::vec3(5.0f);
		groupMesh->AddChild(floor);
		groupMesh->AddChild(wall);

		// Model
		ModelLoader loader;

		Mesh* sponza = new Mesh("Sponza");
		loader.LoadModel("Resources/Models/gltf/sponza/sponza.gltf", sponza);
		sponza->Scale = glm::vec3(0.02f);

		Mesh* flightHelmet = new Mesh("FlightHelmet");
		loader.LoadModel("Resources/Models/gltf/FlightHelmet/FlightHelmet.gltf", flightHelmet);
		flightHelmet->Position.x = -2 * offset;
		flightHelmet->Scale = glm::vec3(5.0f);

		Mesh* damagedHelmet = new Mesh("DamagedHelmet");
		loader.LoadModel("Resources/Models/gltf/damagedHelmet/damagedHelmet.gltf", damagedHelmet);
		damagedHelmet->Rotation.x = 3.14f / 2;
		damagedHelmet->Position.y = 1.5f;

		Mesh* boomBox = new Mesh("BoomBox");
		loader.LoadModel("Resources/Models/gltf/BoomBox/BoomBox.gltf", boomBox);
		boomBox->Position.x = 2 * offset;
		boomBox->Position.y = 1.5f;
		boomBox->Rotation.y = 3.14f;
		boomBox->Scale = glm::vec3(80.0f);

		m_Scene->AddChild(groupMesh);
		m_Scene->AddChild(sponza);
		m_Scene->AddChild(flightHelmet);
		m_Scene->AddChild(damagedHelmet);
		m_Scene->AddChild(boomBox);

		// Point lights
		PointLight* redPointLight = new PointLight("Red", glm::vec3(1.0f, 0.0f, 0.0f));
		redPointLight->Position.y = 1.0f;
		PointLight* greenPointLight = new PointLight("Green", glm::vec3(0.0f, 1.0f, 0.0f));
		greenPointLight->Position.y = 2.0f;
		PointLight* bluePointLight = new PointLight("Blue", glm::vec3(0.0f, 0.0f, 1.0f));
		bluePointLight->Position.y = 3.0f;

		m_Scene->AddChild(redPointLight);
		m_Scene->AddChild(greenPointLight);
		m_Scene->AddChild(bluePointLight);

		// Directional light
		DirectionalLight* directionalLight = new DirectionalLight("Directional");
		directionalLight->Position = glm::vec3(0.3f, 1.0f, -0.2f);
		m_Scene->AddChild(directionalLight);
	}

	void Run()
	{
		while (!m_Window->ShouldClose())
		{
			// Input polling and processing
			ProcessInput();

			// Rendering commands
			m_Renderer->Clear();
			m_Window->Update();
			m_Scene->Update();

			// Render objects
			m_Renderer->Draw(*m_Scene, *m_Camera);


#pragma region ImGUI
			ImGui::Begin("Scene Settings");
			{
				m_Scene->OnGui();
			}
			ImGui::DragFloat("Gamma", (float*)&(*m_Renderer).Gamma, 0.05f, 0.0f, 2.2f);
			ImGui::Text("%.2f ms %.2f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();


#pragma endregion

			m_Window->PostUpdate();
		}
	}
	
	void Terminate()
	{
		// Cleanup
		delete m_Renderer;
		delete m_Window;
		delete m_Scene;
		delete m_Camera;
	}

	void ProcessInput()
	{
		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_Window->GetWindow(), true);

		if (glfwGetMouseButton(m_Window->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			double mouseX, mouseY;

			glfwGetCursorPos(m_Window->GetWindow(), &mouseX, &mouseY);

			float xpos = static_cast<float>(mouseX);
			float ypos = static_cast<float>(mouseY);

			if (m_FirstMouse)
			{
				m_LastX = xpos;
				m_LastY = ypos;
				m_FirstMouse = false;
			}

			float xoffset = xpos - m_LastX;
			float yoffset = m_LastY - ypos; // reversed since y-coordinates go from bottom to top
			m_Camera->Rotate(xoffset, yoffset);

			m_LastX = xpos;
			m_LastY = ypos;
		}

		if (glfwGetMouseButton(m_Window->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_FirstMouse = true;
		}

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->Position += m_Camera->speed * m_Camera->Forward;

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->Position += m_Camera->speed * (-m_Camera->Forward);

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->Position += m_Camera->speed * (-m_Camera->Right);

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->Position += m_Camera->speed * m_Camera->Right;

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
			m_Camera->Position += m_Camera->speed * m_Camera->Up;

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			m_Camera->Position += m_Camera->speed * (-m_Camera->Up);

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			m_Camera->speed = 0.15f;

		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
			m_Camera->speed = 0.05f;
	}

	static void OnResize(GLFWwindow* window, int width, int height)
	{
		// camera.OnReize(width, height);
		glViewport(0, 0, width, height);
	}
};

int main()
{
	RendererApplication* application = new RendererApplication(1280, 720);
	application->Init();
	application->Run();	// Main render loop
	application->Terminate();
	delete application;
}