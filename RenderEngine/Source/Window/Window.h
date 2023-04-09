#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>

class Window
{
private:
	unsigned int m_Width;
	unsigned int m_Height;
	const char* m_Title;
	GLFWwindow* m_Window;
	
public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	void Update();
	bool ShouldClose();
	bool Init();
	void Destroy();
	void PostUpdate();

	void ResizeCallback(unsigned int width, unsigned height);
	
	GLFWwindow* GetWindow() { return m_Window; }

};

