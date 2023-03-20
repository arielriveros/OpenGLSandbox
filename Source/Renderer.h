#pragma once
#include "Window.h"
#include "Shader/Shader.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "VertexArray/VertexArray.h"
#include "Texture/Texture.h"

class Renderer
{
private:
	
public:
	Renderer();
	~Renderer();

	void Init();
	void Clear() const;
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void Shutdown();

};

void APIENTRY GLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);