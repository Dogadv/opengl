#pragma once

#include <cstdint>
#include <vector>

#include <GL/glew.h>

struct VertexBufferEntry
{
    uint32_t type;
    uint32_t count;
    uint8_t size;
    uint8_t normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
            : m_stride(0) {}

    template<typename T>
    void push(uint32_t count)
    {
        static_assert(false);
    }

    template<>
    void push<GLfloat>(uint32_t count)
    {
        uint8_t size = sizeof(GLfloat);

        m_entries.push_back({GL_FLOAT, count, size, GL_FALSE});
        m_stride += count * size;
    }

    template<>
    void push<GLuint>(uint32_t count)
    {
        uint8_t size = sizeof(GLuint);

        m_entries.push_back({GL_UNSIGNED_INT, count, size, GL_FALSE});
        m_stride += count * size;
    }

    inline const std::vector<VertexBufferEntry> &getEntries() const { return m_entries; }
    inline uint32_t getStride() const { return m_stride; }

private:
    std::vector<VertexBufferEntry> m_entries;
    uint32_t m_stride;
};