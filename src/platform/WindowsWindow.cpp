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

WindowsWindow::WindowsWindow(const std::string &title, uint32_t width, uint32_t height)
        : m_title(title),
          m_width(width),
          m_height(height)
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
}

void WindowsWindow::update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}
