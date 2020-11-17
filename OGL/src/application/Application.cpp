#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "../buffer/vertex/VertexBuffer.h"
#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"

static void incrementColorValue(float_t &increment, float_t &color)
{
    if (color > 1.0f || color < 0.0f)
        increment *= -1;

    color += increment;
}

void GLAPIENTRY onGLError(GLenum source,
             GLenum type,
             GLuint id,
             GLenum severity,
             GLsizei length,
             const GLchar* message,
             const void* userParam)
{
    std::cout << "type: " << type << ";message: " << message << std::endl;
    //__debugbreak();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(onGLError, 0);

    std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << std::endl;

    const uint32_t TRIANGLE_VERTEX_COUNT = 4;
    const uint32_t VERTEX_COMPONENT_COUNT = 2;
    float positions[TRIANGLE_VERTEX_COUNT * VERTEX_COMPONENT_COUNT] = {
        -.5f, -.5f,
         .5f,  -.5f,
         .5f,  .5f,
        -.5f,  .5f
    };

    const uint32_t VBO_SIZE = sizeof(positions);

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, VBO_SIZE);
    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.push<GLfloat>(VERTEX_COMPONENT_COUNT);
    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    const uint32_t INDECIES_COUNT = 6;
    uint32_t indecies[INDECIES_COUNT] = {
       0, 1, 2,
       2, 3, 0
    };

    const uint32_t IBO_SIZE = sizeof(indecies);
    IndexBuffer indexBuffer(indecies, INDECIES_COUNT);

    ShaderProgram shaderProgram = ParseShader("res/shaders/Basic.shader");
    uint32_t shader = createShader(shaderProgram.VertexShader, shaderProgram.FragmentShader);

    glUseProgram(shader);

    float_t r = 0.0f;
    float_t g = 0.3f;
    float_t b = 0.9f;
    float_t i_r = 0.003f;
    float_t i_g = 0.003f;
    float_t i_b = 0.003f;

    int32_t uniformLocation = glGetUniformLocation(shader, "u_Color");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        incrementColorValue(i_r, r);
        incrementColorValue(i_g, g);
        incrementColorValue(i_b, b);

        glUniform4f(uniformLocation, r, g, b, 1.0f);

        indexBuffer.bind();

        glDrawElements(GL_TRIANGLES, INDECIES_COUNT, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}