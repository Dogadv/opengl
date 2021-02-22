#include "Renderer.h"

#include<string>

Renderer::Renderer(const std::string &title, uint32_t width, uint32_t height, OrthographicCamera &camera)
        : m_camera(camera)
{
    m_window = Window::create(title, width, height);

    /* 
     * TODO: Abstract and improve inputs!
     *       - Platform indepentent inputs;
     */

    glfwSetWindowUserPointer(m_window->getNativeWindow(), this);
    glfwSetKeyCallback(m_window->getNativeWindow(), [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Renderer &renderer = *(Renderer *) glfwGetWindowUserPointer(window);

        // TODO: temporary solution
        float cameraTranslationDelta = 10.0f;

        switch (action)
        {
            case GLFW_PRESS:
            case GLFW_REPEAT:
            {
                switch (key)
                {
                    case GLFW_KEY_W:
                        renderer.translateCamera(glm::vec3(0, cameraTranslationDelta, 0));
                        break;
                    case GLFW_KEY_A:
                        renderer.translateCamera(glm::vec3(-cameraTranslationDelta, 0, 0));
                        break;
                    case GLFW_KEY_S:
                        renderer.translateCamera(glm::vec3(0, -cameraTranslationDelta, 0));
                        break;
                    case GLFW_KEY_D:
                        renderer.translateCamera(glm::vec3(cameraTranslationDelta, 0, 0));
                        break;
                }
                break;
            }
        }
    });
}

void Renderer::translateCamera(glm::vec3 cameraTranslation)
{
    m_camera.moveBy(cameraTranslation);
}

void Renderer::setKeyCallback(GLFWkeyfun callback) const
{
    // TODO: improve key callbacks
}

/* Loop until the user closes the window */
bool Renderer::isRunning() const
{
    return !glfwWindowShouldClose(m_window->getNativeWindow()) && !m_shouldClose;
}

void Renderer::clear() const
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::update() const
{
    /* Swap front and back buffers */
    glfwSwapBuffers(m_window->getNativeWindow());

    /* Poll for and process events */
    glfwPollEvents();
}

void Renderer::draw(
        const VertexArray &vertexArray,
        const IndexBuffer &indexBuffer
) const
{
    vertexArray.bind();
    indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}