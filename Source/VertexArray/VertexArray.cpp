#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArray::~VertexArray()
{
	
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::Delete() const
{
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

void VertexArray::AttachVertexBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	Bind();
	vbo.Bind();
	const std::vector<VertexBufferAttributeInfo>& attributes = layout.GetAttributes();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attributes.size(); i++)
	{
		const VertexBufferAttributeInfo& attribute = attributes[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,
			attribute.count,
			attribute.type,
			attribute.normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*) offset
		);
		offset += attribute.count * VertexBufferAttributeInfo::GetSizeOfType(attribute.type);
		
	}
	
}
