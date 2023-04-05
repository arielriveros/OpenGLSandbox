#include "PostProcess.h"
#include <glad/glad.h>

PostProcess::PostProcess()
{

}

PostProcess::PostProcess(unsigned int width, unsigned int height, Shader* shader)
{
	m_Width = width;
	m_Height = height;
	m_Shader = shader;
	m_PostProcessFBO = Framebuffer(width, height);
	m_PostProcessFBO.Bind();
	m_PostProcessFBO.AttachColor();
}

PostProcess::~PostProcess()
{
}

void PostProcess::Init()
{
	float quadVertices[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_QuadVAO);
	glGenBuffers(1, &m_QuadVBO);
	glBindVertexArray(m_QuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1); // Tex coord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	m_PostProcessFBO.CheckCompletion();
	m_Shader->SetInt("screenTexture", 0);
	m_PostProcessFBO.Unbind();
}

void PostProcess::Draw() const
{
	m_Shader->Bind();
	glBindVertexArray(m_QuadVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, m_PostProcessFBO.GetColorBufferID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostProcess::Clear() const
{
	m_PostProcessFBO.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_PostProcessFBO.Unbind();
}

void PostProcess::Bind() const
{
	m_PostProcessFBO.Bind();
}

void PostProcess::Unbind() const
{
	m_PostProcessFBO.Unbind();
}

