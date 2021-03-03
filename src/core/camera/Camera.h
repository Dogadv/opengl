#ifndef camera
#define camera

#include <memory>
#include <functional>
#include <glm/glm.hpp>

enum class CameraType
{
    Orthographic,
    Perspective
};

class Camera
{
public:
    Camera() = default;
    virtual ~Camera() = default;

    [[nodiscard]] glm::mat4 getProjectionMatrix() const { return m_projection; }
    [[nodiscard]] glm::mat4 getViewMatrix() const { return m_view; }
    [[nodiscard]] glm::mat4 getViewProjectionMatrix() const { return m_viewProjection; }

    [[nodiscard]] glm::vec3 getPosition() const { return m_position; }

protected:
    glm::mat4 m_projection = glm::mat4(1.0f);
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_viewProjection = glm::mat4(1.0f);

    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
};

#endif