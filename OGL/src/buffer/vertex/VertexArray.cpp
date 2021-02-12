#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_rendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererId);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_rendererId);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& vertexBufferLayout)
{
	bind();
	//vertexBuffer.bind();

	const auto& entries = vertexBufferLayout.getEntries();
	uint32_t offset = 0;

	for (uint32_t i = 0; i < entries.size(); i++)
	{
		const auto& entry = entries[i];

		glEnableVertexArrayAttrib(vertexBuffer.getRendererId(), i);
		glVertexAttribPointer(i, entry.count, entry.type, entry.normalized, vertexBufferLayout.getStride(), (const void*) offset);
	
		offset += entry.count * entry.size;
	}
}
