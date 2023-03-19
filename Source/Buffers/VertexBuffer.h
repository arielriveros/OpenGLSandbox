#pragma once

class VertexBuffer
{
private:
	unsigned int m_BufferID;

public:
	VertexBuffer();
	~VertexBuffer();
	
	void UploadData(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
};