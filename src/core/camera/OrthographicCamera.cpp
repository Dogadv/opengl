#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
    setProjection(left, right, bottom, top);
}

void OrthographicCamera::setPosition(glm::vec3 position)
{
    m_position = position;
    recalculateViewProjection();
}
void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
{
    m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    recalculateViewProjection();
}

void OrthographicCamera::recalculateViewProjection()
{
    m_view = glm::translate(glm::mat4(1.0f), m_position);
    m_viewProjection = m_projection * m_view;
}
