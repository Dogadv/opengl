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
    glfwSwapInterval(1);

    /* Initialize GLEW */
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(onGLError, 0);

    std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << "\n" << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Renderer& renderer = *(Renderer*) glfwGetWindowUserPointer(window);

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

    projection = glm::ortho(.0f, (float) width, .0f, (float) height);
}

void Renderer::translateCamera(glm::vec3 cameratranslation)
{
    cameraPosition += cameratranslation;
}

void Renderer::setKeyCallback(GLFWkeyfun callback) const
{
    // TODO: improve key callbacks
}

/* Loop until the user closes the window */
bool Renderer::isRunning() const
{
    return !glfwWindowShouldClose(m_window);
}

void Renderer::clear() const
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
}

void Renderer::update() const
{
    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Renderer::draw(
    const VertexArray& vertexArray,
    const IndexBuffer& indexBuffer
) const
{
    vertexArray.bind();
	indexBuffer.bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}