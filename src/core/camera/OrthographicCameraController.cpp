#include "OrthographicCameraController.h"

OrthographicCameraController::OrthographicCameraController(Input &input, float aspectRation)
        : m_input(input),
          m_aspectRatio(aspectRation),
          m_zoom(2.0f)
{
    m_camera = OrthographicCamera(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
    m_position = m_camera.getPosition();
}

void OrthographicCameraController::update()
{
    if (m_input.isKeyPressed(GLFW_KEY_W)) m_position += glm::vec3(0.0, -cameraSpeed, 0.0);
    else if (m_input.isKeyPressed(GLFW_KEY_S)) m_position += glm::vec3(0.0, cameraSpeed, 0.0);
    if (m_input.isKeyPressed(GLFW_KEY_A)) m_position += glm::vec3(cameraSpeed, 0.0, 0.0);
    else if (m_input.isKeyPressed(GLFW_KEY_D)) m_position += glm::vec3(-cameraSpeed, 0.0, 0.0);

    m_camera.setPosition(m_position);
}
void OrthographicCameraController::resize(uint32_t width, uint32_t height)
{
    m_aspectRatio = (float) width / (float) height;
    m_camera.setProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
}

glm::mat4 OrthographicCameraController::getViewProjectionMatrix()
{
    return m_camera.getViewProjectionMatrix();
}
