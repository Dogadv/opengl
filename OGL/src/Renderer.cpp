#include "Renderer.h"

#include<iostream>
#include<string>

void GLAPIENTRY onGLError(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cout <<
        "ERROR: " << type <<
        "\nMessage: " << message <<
        "\n" << std::endl;
    //__debugbreak();
}

Renderer::Renderer(const std::string& title, const uint32_t width, const uint32_t height)
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

    /* Initialize GLEW */
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(onGLError, 0);

    std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << "\n" << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    projection = glm::ortho(.0f, (float) width, .0f, (float) height);

    // Hardcoded offset values for testing purpose
    view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    model = glm::translate(glm::mat4(1.0f), glm::vec3(225, -15, 0));
}

/* Loop until the user closes the window */
bool Renderer::isRunning() const
{
    return !glfwWindowShouldClose(m_window);
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer) const
{
	indexBuffer.bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();
}