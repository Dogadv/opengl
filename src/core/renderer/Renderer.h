#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"

#include "../application/Window.h"

#include "../camera/OrthographicCamera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer
{
public:
    Renderer(const std::string &title, uint32_t width, uint32_t height, OrthographicCamera &camera);

    [[nodiscard]] bool isRunning() const;
    void clear() const;
    void update() const;

    void draw(
            const VertexArray &vertexArray,
            const IndexBuffer &indexBuffer
    ) const;

    void setKeyCallback(GLFWkeyfun callback) const;
    void translateCamera(glm::vec3 cameraTranslation);

    [[nodiscard]] Window &getWindow() const { return *m_window; }

    [[nodiscard]] glm::mat4 getMVPMatrix(const glm::vec3 modelTranslation, const float zoom) const
    {
        glm::vec3 cameraPosition = m_camera.getCameraPosition();
        float cameraZoom = m_camera.getZoom();

        glm::mat4 projectionMatrix = m_camera.getProjection();
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), modelTranslation);
        glm::mat4 viewMatrix = glm::scale(
                glm::translate(glm::mat4(1.0f), cameraPosition),
                glm::vec3(cameraZoom, cameraZoom, 1)
        );

        return projectionMatrix * viewMatrix * modelMatrix;
    }

private:
    OrthographicCamera &m_camera;
    std::unique_ptr<Window> m_window;

    bool m_shouldClose = false;
};