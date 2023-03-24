#include <imgui/imgui.h>
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Mesh/Mesh.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Lighting/PointLight.h"
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <stb/stb_image.h>
#include "../Resources/Misc/Geometries.h"
#include "../Resources/Misc/Materials.h"
#include "Model/Model.h"

const unsigned int _WIDTH = 800;
const unsigned int _HEIGHT = 600;

void processInput(GLFWwindow* window, Camera& camera);
bool firstMouse = true;
float lastX = _WIDTH / 2.0;
float lastY = _HEIGHT / 2.0;
stbi_io_callbacks io;

int main()
{
	// Window context setup
    Window window = Window(_WIDTH, _HEIGHT, "Sandbox");
    if (!window.Init())
        return -1;

    Renderer renderer = Renderer();
    renderer.Init();

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Floor
	Mesh floor = Mesh(squareGeometry, Materials::copper);
	floor.EulerRotation.x = 3.14 / 2;
	floor.Position.y = -0.5;
	floor.Scale = glm::vec3(3.0f);

	// Pyramid
	Mesh pyramid = Mesh(pyramidGeometry, Materials::silver);
	pyramid.Position.x -= 1.0f;
	pyramid.Scale = glm::vec3(0.5f);

	// Wall
	Mesh wall = Mesh(squareGeometry, Materials::yellow_plastic);
	wall.Position.y = 1.0f;
	wall.Position.z = -1.5f;
	wall.EulerRotation.x = 3.14f;
	wall.EulerRotation.z = 3.14f / 2.0f;
	wall.Scale = glm::vec3(3.0f);


	// Cube
	Mesh cube = Mesh(cubeGeometry, Materials::ruby);
	cube.Scale = glm::vec3(0.5f);

	// Point light
	PointLight pointLight = PointLight(glm::vec3(0.33f));
	pointLight.Specular = glm::vec3(0.1f);
	pointLight.Position = glm::vec3(0.0f, 0.5f, 0.0f);
	renderer.AddPointLight(pointLight);
	bool rotateLight = true;

	// More Point lights
	PointLight pointLight2 = PointLight(glm::vec3(0.0f, 0.0f, 1.0f));
	pointLight2.Position = glm::vec3(1.0f, 2.5f, -1.0f);

	PointLight pointLight3 = PointLight(glm::vec3(0.0f, 1.0f, 0.0f));
	pointLight3.Position = glm::vec3(1.0f, 0.5f, 1.0f);

	PointLight pointLight4 = PointLight(glm::vec3(1.0f, 0.0f, 0.0f));
	pointLight4.Position = glm::vec3(-1.0f, 0.5f, -1.0f);

	renderer.AddPointLight(pointLight2);
	renderer.AddPointLight(pointLight3);
	renderer.AddPointLight(pointLight4);

	// Directional light
	DirectionalLight directionalLight = DirectionalLight();
	directionalLight.Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	renderer.AddDirectionalLight(directionalLight);

	// Model
	//Model backpack = Model("Resources/Models/backpack/backpack.obj");
	//Model sponza = Model("Resources/Models/sponza/sponza.obj");
	//Model nanosuit = Model("Resources/Models/nanosuit/nanosuit.obj");


	Camera camera = Camera(_WIDTH, _HEIGHT, glm::vec3(0.0f, 1.0f, 4.0f));

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

		// Change object properties
		pyramid.EulerRotation.y = (float)glfwGetTime()/2;
		pyramid.Position.y = cos((float)glfwGetTime())/4;

		cube.EulerRotation.x = (float)glfwGetTime()/2;
		cube.EulerRotation.z = (float)glfwGetTime();

		if (rotateLight)
		{
			pointLight.Position.x = cos((float)glfwGetTime()/2);
			pointLight.Position.z = sin((float)glfwGetTime()/2);
		}
		
		// Render meshes
		renderer.Draw(floor, camera);
		renderer.Draw(pyramid, camera);
		renderer.Draw(cube, camera);
		renderer.Draw(wall, camera);

		//renderer.Draw(backpack, camera);
		//renderer.Draw(sponza, camera);
		//renderer.Draw(nanosuit, camera);
		
		renderer.DrawLights(camera);

#pragma region ImGUI
		ImGui::Begin("Settings");

		ImGui::SeparatorText("Lighting");
		{
			ImGui::Text("Directional Light settings");
			ImGui::ColorEdit3("Dir Diffuse", (float*)&directionalLight.Diffuse);
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("DirX", (float*)&directionalLight.Direction.x, 0.1f, -1.0f, 1.0f);
			ImGui::SameLine(0.0f, 0.0f);

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("DirY", (float*)&directionalLight.Direction.y, 0.1f, -1.0f, 1.0f);
			ImGui::SameLine(0.0f, 0.0f);

			ImGui::PushItemWidth(100);
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::DragFloat("DirZ", (float*)&directionalLight.Direction.z, 0.1f, -1.0f, 1.0f);

			ImGui::Text("Point Light settings");
			ImGui::ColorEdit3("Diffuse",  (float*)&pointLight.Diffuse);
			ImGui::ColorEdit3("Specular", (float*)&pointLight.Specular);
			ImGui::ColorEdit3("Ambient",  (float*)&pointLight.Ambient);
			ImGui::Checkbox("Rotate", &rotateLight);
			ImGui::DragFloat("Constant", (float*)&pointLight.Constant, 0.1f, 0.0f, 5.0f);
			ImGui::DragFloat("Linear", (float*)&pointLight.Linear, 0.1f, 0.0f, 5.0f);
			ImGui::DragFloat("Quadratic", (float*)&pointLight.Quadratic, 0.1f, 0.0f, 5.0f);
		}

		ImGui::Text("%.1f FPS %.3f ms", 1000.0f / io.Framerate, io.Framerate);

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


}