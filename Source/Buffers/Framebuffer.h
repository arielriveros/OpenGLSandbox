#pragma once

class Framebuffer
{
private:
	unsigned int m_BufferID;
	unsigned int m_RenderBufferID;
	unsigned int m_Width = 0, m_Height = 0;
	unsigned int m_ColorBufferID;
	unsigned int m_DepthBufferID;

public:
	Framebuffer();
	Framebuffer(unsigned int width, unsigned int height);
	~Framebuffer();

	void Bind() const;
	void Unbind() const;
	void Delete() const;
	void AttachColor();
	void AttachDepth();
	void CheckCompletion() const;

	unsigned int GetColorBufferID() const { return m_ColorBufferID; }
};