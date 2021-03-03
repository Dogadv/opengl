#include <glm/glm.hpp>

#include "Camera.h"
#include "../input/Input.h"

class CameraController
{
public:
    virtual ~CameraController() = default;

    virtual void update() = 0;
    virtual void resize(uint32_t width, uint32_t height) = 0;

    virtual glm::mat4 getViewProjectionMatrix() = 0;

    static std::unique_ptr<CameraController> create(CameraType cameraType, Input& input, float aspectRation);
};


