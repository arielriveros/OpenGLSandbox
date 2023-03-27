#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	bool Init(GLFWframebuffersizefun callback);
	void Destroy();
	void SwapBuffersAndPollEvents();
	
	GLFWwindow* GetWindow() { return m_Window; }

private:
	static void OnResize_callback(GLFWwindow* window, int width, int height);

};

