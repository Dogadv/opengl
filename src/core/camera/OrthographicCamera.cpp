#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float width, float height)
        : m_position({0.0f, 0.0f, 0.0f}),
          m_projection(glm::ortho(.0f, width, .0f, height)),
          m_zoom(1.0f),
          m_angle(0.0f) {}

void OrthographicCamera::moveBy(glm::vec3 delta)
{
    m_position += delta;
}

void OrthographicCamera::setPosition(glm::vec3 destination)
{
    m_position = destination;
}

void OrthographicCamera::zoomBy(float delta)
{
    m_zoom += delta;
}

void OrthographicCamera::setZoom(float zoom)
{
    m_zoom = zoom;
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
