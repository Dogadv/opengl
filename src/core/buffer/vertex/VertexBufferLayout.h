#pragma once

#include <cstdint>
#include <vector>

#include <GL/glew.h>

enum class VertexDataType
{
    FLOAT, FLOAT2, FLOAT3, FLOAT4, INT
};

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
    void set()
    {
        static_assert(false);
    }

    inline const std::vector<VertexBufferEntry> &getEntries() const { return m_entries; }

    template<>
    void set<Vertex>()
    {
        m_entries.push_back(
                {GL_FLOAT, VERTEX_POSITION_COMPONENT_COUNT, sizeof(GLfloat), GL_FALSE}
        );
        m_entries.push_back(
                {GL_FLOAT, VERTEX_COLOR_COMPONENT_COUNT, sizeof(GLfloat), GL_FALSE}
        );
        m_entries.push_back(
                {GL_FLOAT, VERTEX_TEXTURE_COORD_COMPONENT_COUNT, sizeof(GLfloat), GL_FALSE}
        );
        m_entries.push_back(
                {GL_UNSIGNED_INT, VERTEX_TEXTURE_INDEX_COMPONENT_COUNT, sizeof(GLuint), GL_FALSE}
        );

        m_stride = sizeof(Vertex);
    }
    inline uint32_t getStride() const { return m_stride; }

private:
    std::vector<VertexBufferEntry> m_entries;
    uint32_t m_stride;
};