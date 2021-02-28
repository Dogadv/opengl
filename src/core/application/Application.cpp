#include "Application.h"

#include<string>

Application::Application(const std::string &title, uint32_t width, uint32_t height, OrthographicCamera &camera)
        : m_camera(camera)
{

    WindowEventsListener windowEventsListener = [this](WindowEvents event) {
        onEvent(event);
    };

    m_window = Window::create(title, width, height, windowEventsListener);
    m_input = std::make_unique<Input>(m_window->getNativeWindow());
}

bool Application::isRunning() const
{
    return !glfwWindowShouldClose(m_window->getNativeWindow()) && !m_shouldClose;
}

void Application::clear() const
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Application::onEvent(WindowEvents event)
{
    switch (event)
    {
        case WindowEvents::OnResize:
        {
            uint32_t width = m_window->getWidth();
            uint32_t height = m_window->getHeight();

            m_camera.resize(width, height);
        }
            break;
        case WindowEvents::OnClose:
            // TODO: Implement
            break;
    }
}
