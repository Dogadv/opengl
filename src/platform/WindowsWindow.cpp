#include "WindowsWindow.h"

void GLAPIENTRY onGLError(GLenum source,
                          GLenum type,
                          GLuint id,
                          GLenum severity,
                          GLsizei length,
                          const GLchar *message,
                          const void *userParam)
{
    std::cout <<
              "ERROR: " << type <<
              "\nMessage: " << message <<
              "\n" << std::endl;
    //__debugbreak();
}

WindowsWindow::WindowsWindow(
        const std::string &title,
        uint32_t width,
        uint32_t height,
        WindowEventsListener &windowCallback,
        ScrollEventsListener &scrollCallback
        )
        : m_title(title),
          m_width(width),
          m_height(height),
          m_windowEventCallback(windowCallback),
          m_scrollEventCallback(scrollCallback)
{
    /* Initialize the library */
    if (!glfwInit()) __debugbreak();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        __debugbreak();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    /* Initialize GLEW */
    glewInit();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(onGLError, nullptr);

    std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << "\n" << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *nativeWindow, int width, int height)
    {
        WindowsWindow &window = *(WindowsWindow *) glfwGetWindowUserPointer(nativeWindow);

        window.resize(width, height);
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *nativeWindow, double xOffset, double yOffset)
    {
        WindowsWindow &window = *(WindowsWindow *) glfwGetWindowUserPointer(nativeWindow);

        window.offsetZoom((int32_t) yOffset);
    });
}

void WindowsWindow::update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}
void WindowsWindow::resize(int32_t width, int32_t height)
{
    m_width = width;
    m_height = height;

    m_windowEventCallback(WindowEvents::OnResize);
    glViewport(0, 0, width, height);
}

void WindowsWindow::offsetZoom(int32_t offset)
{
    if (offset > 0) m_scrollEventCallback(ScrollEvents::OnScrollUp);
    else m_scrollEventCallback(ScrollEvents::OnScrollDown);
}
