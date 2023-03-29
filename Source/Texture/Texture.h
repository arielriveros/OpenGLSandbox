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
	std::string m_Directory;
	std::string m_FileName;

public:
	Texture() {};
	Texture(const std::string& name);
	Texture(const std::string& directory, std::string fileName, const char* type, bool flipY = false, bool correctedGamma = false);
	~Texture();

	void Activate(unsigned int slot = 0) const;
	void Bind() const;
	void Load(bool flipVertically, bool repeat = true, bool correctedGamma = false);
	void Unbind() const;
	void Delete() const;

	inline unsigned int ID() const { return m_TextureID; }
	inline std::string Directory() const { return m_Directory; }
	inline std::string FileName() const { return m_FileName; }
	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
};