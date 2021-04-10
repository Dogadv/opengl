#include "CameraController.h"
#include "OrthographicCamera.h"

class OrthographicCameraController : public CameraController
{
public:
    OrthographicCameraController(Input &input, float aspectRation);
    ~OrthographicCameraController() = default;

    void update() override;
    void resize(uint32_t width, uint32_t height) override;
    void zoomBy(float offset) override;

    glm::mat4 getViewProjectionMatrix() override;

    [[nodiscard]] OrthographicCamera getCamera() { return m_camera; }
    [[nodiscard]] const OrthographicCamera &getCamera() const { return m_camera; }

private:
    Input &m_input;
    OrthographicCamera m_camera;

    float m_zoom = 1.0f;
    float m_aspectRatio;

    float cameraSpeed = 0.05f;

    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
};