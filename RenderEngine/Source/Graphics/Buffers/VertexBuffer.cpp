#include "VertexBuffer.h"
#include <glad/gl.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

VertexBuffer::~VertexBuffer()
{
	
}

void VertexBuffer::UploadData(const void* data, unsigned int size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete() const
{
	glDeleteBuffers(1, &m_BufferID);
}
