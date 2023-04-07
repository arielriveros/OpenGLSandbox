#include "IndexBuffer.h"
#include <glad/gl.h>

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &m_IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	m_indicesCount = 0;
}

IndexBuffer::~IndexBuffer()
{
	
}

void IndexBuffer::UploadData(const unsigned int* data, unsigned int count)
{
	Bind();
	m_indicesCount = count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Delete() const
{
	glDeleteBuffers(1, &m_IndexBufferID);
}
