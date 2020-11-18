#pragma once

#include "buffer/vertex/VertexArray.h"
#include "buffer/index/IndexBuffer.h"

class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer) const;
};