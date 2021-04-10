#include "../../pch.h"

#include <string>
#include <memory>

#include "Window.h"

#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../camera/CameraController.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Application
{
public:
    Application(const std::string &title, uint32_t width, uint32_t height, CameraType cameraType);

    [[nodiscard]] bool isRunning() const;
    void clear() const;
    void update() const;
    void shutdown() const;

    void draw(
            const VertexArray &vertexArray,
            const IndexBuffer &indexBuffer
    ) const;

    void onWindowEvent(WindowEvents event);
    void onScrollEvent(ScrollEvents event);

    [[nodiscard]] Input &getInput() const { return *m_input; }
    [[nodiscard]] Window &getWindow() const { return *m_window; }

    [[nodiscard]] glm::mat4 getMVPMatrix(const glm::vec3 modelTranslation) const
    {
        glm::mat4 viewProjectionMatrix = m_cameraController->getViewProjectionMatrix();
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), modelTranslation);

        return viewProjectionMatrix * modelMatrix;
    }

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Input> m_input;
    std::unique_ptr<CameraController> m_cameraController;

    bool m_shouldClose = false;
};