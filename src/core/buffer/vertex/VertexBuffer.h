#pragma once

#include "../../entity/Vertex.h"

#include <cstdint>

class VertexBuffer
{
public:
	VertexBuffer(GLuint size);
	~VertexBuffer();

	void bind(Vertex* vertices, GLuint size) const;
	void unbind() const;

    [[nodiscard]] inline uint32_t getRendererId() const { return m_rendererId; }

private:
	uint32_t m_rendererId;
};