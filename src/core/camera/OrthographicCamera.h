#ifndef ortho_camera
#define ortho_camera

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera() = default;
    OrthographicCamera(float left, float right, float bottom, float top);

    void setProjection(float left, float right, float bottom, float top);
    void setPosition(glm::vec3 position);

private:
    void recalculateViewProjection();
};

#endif