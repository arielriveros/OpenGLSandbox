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

const unsigned int _WIDTH = 800;
const unsigned int _HEIGHT = 600;

void processInput(GLFWwindow* window, Camera& camera);
bool firstMouse = true;
float lastX = _WIDTH / 2.0;
float lastY = _HEIGHT / 2.0;

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

	// Group mesh
	Mesh groupMesh;

	// Floor
	Mesh floor = Mesh("floor", squareGeometry, Materials::copper);
	floor.Rotation.x = 3.14 / 2;
	floor.Position.y = -0.5;

	// Wall
	Mesh wall = Mesh("wall", squareGeometry, Materials::ruby);
	wall.Rotation.x = 3.14f;
	wall.Rotation.z = 3.14f / 2.0f;
	wall.Position.z = -0.5f;

	groupMesh.AddChild(&floor);
	groupMesh.AddChild(&wall);

	// Pyramid
	Mesh pyramid = Mesh("pyramid", pyramidGeometry, Materials::silver);
	pyramid.Position.x -= 1.0f;
	pyramid.Scale = glm::vec3(0.5f);

	// Cube
	Texture crate_D("Resources/Images", "cube_albedo.png", "texture_diffuse");
	Texture crate_S("Resources/Images", "cube_specular.png", "texture_specular");
	Mesh cube = Mesh("cube", cubeGeometry, {crate_D , crate_S});
	cube.Position.z = 0.5f;
	cube.Scale = glm::vec3(0.5f);
	groupMesh.AddChild(&cube);

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
	ModelLoader loader;

	Mesh nanosuit, cyborg, damagedHelmet;

	loader.LoadModel("Resources/Models/nanosuit/nanosuit.obj", &nanosuit);
	nanosuit.Position.x -= 1.5f;
	nanosuit.Scale = glm::vec3(0.25f);

	loader.LoadModel("Resources/Models/cyborg/cyborg.obj", &cyborg);
	cyborg.Position.x += 1.5f;

	loader.LoadModel("Resources/Models/damagedHelmet/damagedHelmet.gltf", &damagedHelmet);
	damagedHelmet.Rotation.x = 3.14f / 2.0f;
	damagedHelmet.Position.y = 1.5f;
	

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
		pyramid.Rotation.y = (float)glfwGetTime()/2;
		pyramid.Position.y = cos((float)glfwGetTime())/4;

		cube.Rotation.x = (float)glfwGetTime()/2;
		cube.Rotation.z = (float)glfwGetTime();

		if (rotateLight)
		{
			pointLight.Position.x = cos((float)glfwGetTime()/2);
			pointLight.Position.z = sin((float)glfwGetTime()/2);
		}

		groupMesh.Update();
		pyramid.Update();
		cube.Update();
		nanosuit.Update();
		cyborg.Update();
		damagedHelmet.Update();
		
		// Render meshes
		renderer.Draw(groupMesh, camera);
		renderer.Draw(pyramid, camera);
		renderer.Draw(cube, camera);
		renderer.Draw(nanosuit, camera);
		renderer.Draw(cyborg, camera); 
		renderer.Draw(damagedHelmet, camera);
		
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
		ImGui::SeparatorText("Scene");
		{
			ImGui::Text("Group Transform Settings");
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

			ImGui::Text("Wall Transform Settings");
			{
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Pos X", (float*)&wall.Position.x, 0.1f, -1.0f, 1.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Pos Y", (float*)&wall.Position.y, 0.1f, -1.0f, 1.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Pos Z", (float*)&wall.Position.z, 0.1f, -1.0f, 1.0f);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Rot X", (float*)&wall.Rotation.x, 0.1f, 0.0f, 3.1415f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Rot Y", (float*)&wall.Rotation.y, 0.1f, 0.0f, 3.1415f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Rot Z", (float*)&wall.Rotation.z, 0.1f, 0.0f, 3.1415f);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Scale X", (float*)&wall.Scale.x, 0.1f, 0.0f, 5.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Scale Y", (float*)&wall.Scale.y, 0.1f, 0.0f, 5.0f);

				ImGui::SameLine(0.0f, 0.0f);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Wall Scale Z", (float*)&wall.Scale.z, 0.1f, 0.0f, 5.0f);
			}

			ImGui::Text("Floor Transform Settings");
			{
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Floor Pos X", (float*)&floor.Position.x, 0.1f, -1.0f, 1.0f);
				ImGui::SameLine(0.0f, 0.0f);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Floor Pos Y", (float*)&floor.Position.y, 0.1f, -1.0f, 1.0f);
				ImGui::SameLine(0.0f, 0.0f);

				ImGui::PushItemWidth(100);
				ImGui::SameLine(0.0f, 0.0f);
				ImGui::DragFloat("Floor Pos Z", (float*)&floor.Position.z, 0.1f, -1.0f, 1.0f);
			}

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