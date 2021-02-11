#pragma once

#include<cstdint>
#include <string>

#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& filepath, const GLint slotIndex);
	~Texture();

	void bind() const;
	void unbind() const;

	inline GLuint getRendererId() const { return m_rendererId; }
	inline GLint getSlotIndex() const { return m_slotIndex; }

	inline uint32_t getWidth() const { return m_width; }
	inline uint32_t getHeight() const { return m_height; }

private:
	GLuint m_rendererId;
	GLint m_slotIndex;

	uint8_t* m_localBuffer;
	int32_t m_width, m_height, m_bpp;
};