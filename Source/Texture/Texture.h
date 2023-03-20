#pragma once
#include <iostream>

class Texture
{
private:
	unsigned int m_TextureID;
	int m_Width, m_Height;
	int m_BitsPerPixel;
	unsigned char* m_LocalBuffer;
	std::string m_ImagePath;

public:
	Texture() {};
	Texture(const std::string& imagePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
};