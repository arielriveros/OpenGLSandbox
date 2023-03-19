#pragma once

class IndexBuffer
{
private:
	unsigned int m_IndexBufferID;
	unsigned int m_indicesCount;

public:
	IndexBuffer();
	~IndexBuffer();
	
	void UploadData(const unsigned int* data, unsigned int count);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_indicesCount; }
};