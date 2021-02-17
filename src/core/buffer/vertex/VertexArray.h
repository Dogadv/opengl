#pragma once

#include <cstdint>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& vertexBufferLayout);

	void bind() const;
	void unbind() const;

private:
	uint32_t m_rendererId;
};