#pragma once
#include <iostream>
#include <assimp/scene.h>

class Texture
{
public:
	std::string name;
	std::string type;

private:
	unsigned int m_TextureID;
	int m_Width, m_Height, m_nChannels;
	unsigned char* m_LocalBuffer;
	std::string m_ImagePath;

public:
	Texture() {};
	Texture(const std::string& name);
	Texture(const std::string& imagePath, const char* type);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Load(bool flipVertically, bool repeat = true);
	void Unbind() const;
	void Delete() const;

	inline unsigned int ID() const { return m_TextureID; }
	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
};