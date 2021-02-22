#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class OrthographicCamera
{
public:
    OrthographicCamera(float width, float height);
    virtual ~OrthographicCamera() = default;

    void moveBy(glm::vec3 delta);
    void setPosition(glm::vec3 destination);

    void zoomBy(float delta);
    void setZoom(float zoom);

    void rotateBy(float delta);
    void setDirection(float angle);

    [[nodiscard]] glm::mat4 getProjection() const { return m_projection; }
    [[nodiscard]] glm::vec3 getCameraPosition() const { return m_position; }

    [[nodiscard]] float getZoom() const { return m_zoom; }

private:
    float m_zoom;
    float m_angle;

    glm::mat4 m_projection;
    glm::vec3 m_position;
};