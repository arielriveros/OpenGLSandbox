#include <imgui/imgui.h>
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <stb/stb_image.h>
#include "../Resources/Misc/Geometries.h"
#include "../Resources/Misc/Materials.h"
#include "Loaders/ModelLoader.h"

const unsigned int _WIDTH = 1280;
const unsigned int _HEIGHT = 720;

void processInput(GLFWwindow* window, Camera& camera);
void OnResize_callback(GLFWwindow* window, int width, int height);
bool firstMouse = true;
float lastX = _WIDTH / 2.0;
float lastY = _HEIGHT / 2.0;

int main()
{
	// Window context setup
    Window window = Window(_WIDTH, _HEIGHT, "Sandbox");
    if (!window.Init(OnResize_callback))
        return -1;

    Renderer renderer = Renderer();
    renderer.Init();

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	
	float offset = 2.0f;

	// Floor
	Mesh floor = Mesh("floor", squareGeometry, Materials::turquoise);
	floor.Rotation.x = -3.14f / 2;
	floor.Position.y = -0.5f;

	// Wall
	Texture brickwall_D("Resources/Images/Textures", "brickwall_albedo.jpg", "texture_diffuse");
	Texture brickwall_N("Resources/Images/Textures", "brickwall_normal.jpg", "texture_normal");
	Mesh wall = Mesh("wall", squareGeometry, { brickwall_D, brickwall_N });
	wall.Position.z = -0.5f;

	Mesh groupMesh;
	groupMesh.Position.y = 1.5f;
	groupMesh.Scale = glm::vec3(5.0f);
	groupMesh.AddChild(&floor);
	groupMesh.AddChild(&wall);


	// Model
	ModelLoader loader;

	Mesh sponza;
	loader.LoadModel("Resources/Models/gltf/sponza/sponza.gltf", &sponza);
	sponza.Scale = glm::vec3(0.025f);

	Mesh flightHelmet;
	loader.LoadModel("Resources/Models/gltf/FlightHelmet/FlightHelmet.gltf", &flightHelmet);
	flightHelmet.Position.x = -2 * offset;
	flightHelmet.Scale = glm::vec3(5.0f);

	Mesh cyborg;
	loader.LoadModel("Resources/Models/obj/cyborg/cyborg.obj", &cyborg);
	cyborg.Position.x = -1 * offset;

	Mesh damagedHelmet;
	loader.LoadModel("Resources/Models/gltf/damagedHelmet/damagedHelmet.gltf", &damagedHelmet);
	damagedHelmet.Rotation.x = 3.14f/2;
	damagedHelmet.Position.y = 1.5f;
	
	Mesh backpack;
	loader.LoadModel("Resources/Models/obj/backpack/backpack.obj", &backpack);
	backpack.Position.x = 1 * offset;
	backpack.Position.y = 1.5f;
	backpack.Scale = glm::vec3(0.66f);

	Mesh boomBox;
	loader.LoadModel("Resources/Models/gltf/BoomBox/BoomBox.gltf", &boomBox);
	boomBox.Position.x = 2 * offset;
	boomBox.Position.y = 1.5f;
	boomBox.Rotation.y = 3.14f;
	boomBox.Scale = glm::vec3(80.0f);

	// Point lights
	PointLight redPointLight   = PointLight(glm::vec3(1.0f, 0.0f, 0.0f));
	redPointLight.Position.y = 1.0f;
	PointLight greenPointLight = PointLight(glm::vec3(0.0f, 1.0f, 0.0f));
	greenPointLight.Position.y = 2.0f;
	PointLight bluePointLight  = PointLight(glm::vec3(0.0f, 0.0f, 1.0f));
	bluePointLight.Position.y = 3.0f;

	renderer.AddPointLight(redPointLight);
	renderer.AddPointLight(greenPointLight);
	renderer.AddPointLight(bluePointLight);

	// Directional light
	DirectionalLight directionalLight = DirectionalLight();
	directionalLight.Direction = glm::vec3(1.0f, -1.0f, -1.0f);
	renderer.AddDirectionalLight(directionalLight);

	Mesh scene;
	scene.AddChild(&groupMesh);
	scene.AddChild(&sponza);
	scene.AddChild(&cyborg);
	scene.AddChild(&flightHelmet);
	scene.AddChild(&damagedHelmet);
	scene.AddChild(&backpack);
	scene.AddChild(&boomBox);

	Camera camera = Camera(_WIDTH, _HEIGHT, glm::vec3(0.0f, 1.5f, 3.5f));

	// Main window loop
    while (!window.ShouldClose())
    {
		// Input polling and processing
        processInput(window.GetWindow(), camera);
		
		// Rendering commands
		renderer.Clear();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float dt = (float)glfwGetTime();

		redPointLight.Position.x	= 2 * (offset + 1.0f) * cos(dt);
		redPointLight.Position.z	= 1.0f + sin(dt);

		greenPointLight.Position.x	= 2 * (offset + 1.0f) * sin(dt);
		greenPointLight.Position.z	= -1.0f - cos(dt);

		bluePointLight.Position.x	= 2 * (offset + 1.0f) * cos(dt * 2);
		bluePointLight.Position.z	= 1.0f + cos(dt / 2);

		scene.Update();
		
		// Render objects
		renderer.Draw(scene, camera);
		renderer.DrawLights(camera);

#pragma region ImGUI
		ImGui::Begin("Directional Light settings");
		{
			ImGui::PushItemWidth(100);
			ImGui::ColorEdit3("Dir Diffuse", (float*)&directionalLight.Diffuse);
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("DirX", (float*)&directionalLight.Direction.x, 0.1f, -1.0f, 1.0f);
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("DirY", (float*)&directionalLight.Direction.y, 0.1f, -1.0f, 1.0f);
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("DirZ", (float*)&directionalLight.Direction.z, 0.1f, -1.0f, 1.0f);

		}
		ImGui::End();

		ImGui::Begin("Scene Settings");
		{
			ImGui::Text("Sponza Transform Settings");
			{
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Pos X", (float*)&groupMesh.Position.x, 0.1f, -1.0f, 1.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Pos Y", (float*)&groupMesh.Position.y, 0.1f, -1.0f, 1.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Pos Z", (float*)&groupMesh.Position.z, 0.1f, -1.0f, 1.0f);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Rot X", (float*)&groupMesh.Rotation.x, 0.1f, 0.0f, 3.1415f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Rot Y", (float*)&groupMesh.Rotation.y, 0.1f, 0.0f, 3.1415f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Rot Z", (float*)&groupMesh.Rotation.z, 0.1f, 0.0f, 3.1415f);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Scale X", (float*)&groupMesh.Scale.x, 0.1f, 0.0f, 5.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Scale Y", (float*)&groupMesh.Scale.y, 0.1f, 0.0f, 5.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Group Scale Z", (float*)&groupMesh.Scale.z, 0.1f, 0.0f, 5.0f);
			}
		}

		ImGui::Text("%.2f ms %.2f FPS", 1000.0f / io.Framerate, io.Framerate);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion

        window.SwapBuffersAndPollEvents();
    }


	// Cleanup after stopping loop
    renderer.Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    window.Destroy();
    return 0;
}

// Process Input from keyboard
void processInput(GLFWwindow* window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
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

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
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

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.speed = 0.15f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		camera.speed = 0.05f;
}

void OnResize_callback(GLFWwindow* window, int width, int height)
{
	// camera.OnReize(width, height);
	glViewport(0, 0, width, height);
}