#pragma once
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_VertexArrayID;
	
public:
	VertexArray();
	~VertexArray();
	
	void Bind() const;
	void Unbind() const;
	void Delete() const;
	void AttachVertexBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
};