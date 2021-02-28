#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float width, float height)
        : m_aspectRatio(width / height),
          m_zoom(1.0f),
          m_angle(0.0f),
          m_position({0.0f, 0.0f, 0.0f}),
          m_projection(1.0f),
          m_view(1.0f),
          m_viewProjection(1.0f)
{
    recalculateViewProjection();
}

void OrthographicCamera::moveBy(glm::vec3 delta)
{
    m_position += delta;
    recalculateViewProjection();
}

void OrthographicCamera::setPosition(glm::vec3 destination)
{
    m_position = destination;
    recalculateViewProjection();
}

void OrthographicCamera::zoomBy(float delta)
{
    m_zoom += delta;
    recalculateViewProjection();
}

void OrthographicCamera::setZoom(float zoom)
{
    m_zoom = zoom;
    recalculateViewProjection();
}

void OrthographicCamera::rotateBy(float delta)
{
    // TODO: implement
    __debugbreak();

    m_angle += delta;
}

void OrthographicCamera::setDirection(float angle)
{
    // TODO: implement
    __debugbreak();

    m_angle = angle;
}
void OrthographicCamera::resize(uint32_t width, uint32_t height)
{
    m_aspectRatio = (float) width / (float) height;

    recalculateViewProjection();
}
void OrthographicCamera::recalculateViewProjection()
{
    m_view = glm::translate(glm::mat4(1.0f), m_position);
    m_projection = glm::ortho(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom, -1.0f, 1.0f);

    m_viewProjection = m_projection * m_view;
}
