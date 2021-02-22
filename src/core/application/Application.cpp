#include "Application.h"

#include<string>

Application::Application(const std::string &title, uint32_t width, uint32_t height, OrthographicCamera &camera)
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
        Application &renderer = *(Application *) glfwGetWindowUserPointer(window);

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

void Application::translateCamera(glm::vec3 cameraTranslation)
{
    m_camera.moveBy(cameraTranslation);
}

void Application::setKeyCallback(GLFWkeyfun callback) const
{
    // TODO: improve key callbacks
}

/* Loop until the user closes the window */
bool Application::isRunning() const
{
    return !glfwWindowShouldClose(m_window->getNativeWindow()) && !m_shouldClose;
}

void Application::clear() const
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::update() const
{
    m_window->update();
}

void Application::draw(
        const VertexArray &vertexArray,
        const IndexBuffer &indexBuffer
) const
{
    vertexArray.bind();
    indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Application::shutdown() const
{
    glfwTerminate();
}