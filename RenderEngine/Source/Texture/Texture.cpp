#include "Texture.h"
#include <glad/gl.h>
#include <stb/stb_image.h>

Texture::Texture(const std::string& name)
{
	this->name = name;
	this->type = "none";
	Load(true, true);
}

Texture::Texture(const std::string& directory, std::string fileName, const char* type, bool flipY, bool correctedGamma)
{
	m_Directory = directory;
	m_FileName = fileName;
	m_LocalBuffer = nullptr;
	m_nChannels = 0;
	this->type = type;
	Load(flipY, true, correctedGamma);
}

Texture::~Texture()
{
	
}

void Texture::Activate(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Load(bool flipVertically, bool repeat, bool correctedGamma)
{
	stbi_set_flip_vertically_on_load(flipVertically);
	m_LocalBuffer = stbi_load((m_Directory + "/" + m_FileName).c_str(), &m_Width, &m_Height, &m_nChannels, 0);

	GLenum colorMode = GL_RGB;
	switch (m_nChannels) {
	case 1:
		colorMode = GL_ALPHA;
		break;
	case 4:
		colorMode = GL_RGBA;
		break;
	};

	GLint format = correctedGamma ? GL_SRGB_ALPHA : GL_RGBA8;

	if (m_LocalBuffer)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		if (repeat)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, colorMode, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	else
		std::cout << "Error loading texture: " << m_Directory << "/" << m_FileName << std::endl;
	
	stbi_image_free(m_LocalBuffer);
	Unbind();
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &m_TextureID);
}
