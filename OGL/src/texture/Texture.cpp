#include "Texture.h"

#include <stb_image.h>

Texture::Texture(const std::string& filepath)
	:m_rendererId(0), m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);

	m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

	glGenTextures(1, &m_rendererId);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererId);
}

void Texture::bind(uint32_t slot /* = 0 */) const
{
	glActiveTexture(GL_TEXTURE + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
