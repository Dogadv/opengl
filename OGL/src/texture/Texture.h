#pragma once

#include<cstdint>
#include <string>

#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(uint32_t slot = 0) const;
	void unbind() const;

	inline uint32_t getWidth() const { return m_width; }
	inline uint32_t getHeight() const { return m_height; }

private:
	uint32_t m_rendererId;
	uint8_t* m_localBuffer;
	int32_t m_width, m_height, m_bpp;
};