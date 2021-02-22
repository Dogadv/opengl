#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(GLuint size)
{
    glGenBuffers(1, &m_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererId);
}

void VertexBuffer::bind(Vertex *vertices, GLuint size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
