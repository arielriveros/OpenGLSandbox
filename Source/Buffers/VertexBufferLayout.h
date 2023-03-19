#pragma once
#include <vector>
#include <glad/glad.h>
#include <stdexcept>

struct VertexBufferAttributeInfo
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferAttributeInfo> m_Attributes;
	unsigned int m_Stride;

public:
	VertexBufferLayout() : m_Stride(0) {};
	
	template<typename T>
	void Push(unsigned int count)
	{
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Attributes.push_back({ GL_FLOAT, count, false });
		m_Stride += sizeof(GLfloat) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Attributes.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += sizeof(GLuint) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Attributes.push_back({ GL_UNSIGNED_BYTE, count, false });
		m_Stride += sizeof(GLbyte) * count;
	}

	inline const std::vector<VertexBufferAttributeInfo> GetAttributes() const { return m_Attributes; }
	inline unsigned int GetStride() const { return m_Stride; }
};