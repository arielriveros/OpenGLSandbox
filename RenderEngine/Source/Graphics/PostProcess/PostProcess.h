#pragma once
#include "../Shader/Shader.h"
#include "../Buffers/Framebuffer.h"

class PostProcess
{
private:
	Framebuffer m_PostProcessFBO;
	Shader* m_Shader;
	unsigned int m_Width = 0, m_Height = 0;
	unsigned int m_QuadVAO, m_QuadVBO;

public:
	PostProcess();
	PostProcess(unsigned int width, unsigned int height, Shader* shader);
	~PostProcess();

	void Init();
	void Draw() const;
	void Clear() const;
	void Bind() const;
	void Unbind() const;
};