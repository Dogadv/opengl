#include "OrthographicCameraController.h"

std::unique_ptr<CameraController>
CameraController::create(CameraType cameraType, Input& input, float aspectRation)
{
    switch (cameraType)
    {
        case CameraType::Orthographic:
            return std::make_unique<OrthographicCameraController>(input, aspectRation);
        case CameraType::Perspective:
            static_assert("NOT IMPLEMENTED");
            break;
    }
}
