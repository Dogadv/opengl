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

    void resize(uint32_t width, uint32_t height);

    [[nodiscard]] glm::mat4 getProjectionMatrix() const { return m_projection; }
    [[nodiscard]] glm::mat4 getViewMatrix() const { return m_view; }
    [[nodiscard]] glm::mat4 getViewProjectionMatrix() const { return m_viewProjection; }

    [[nodiscard]] float getZoom() const { return m_zoom; }

private:
    void recalculateViewProjection();

private:
    float m_zoom;
    float m_angle;
    float m_aspectRatio;

    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_viewProjection;
    glm::vec3 m_position;
};