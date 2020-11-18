#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "../buffer/vertex/VertexBuffer.h"
#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../texture/Texture.h"
#include "../shader/Shader.h"
#include "../Renderer.h"

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
    std::cout << 
        "ERROR: " << type <<
        "\nMessage: " << message <<
        "\n" << std::endl;
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

    std::cout << glGetString(GL_VERSION) << "\n" << glGetString(GL_RENDERER) << "\n" << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const uint32_t TRIANGLE_VERTEX_COUNT = 4;
    const uint32_t GEOMETRY_VERTEX_COMPONENT_COUNT = 2;
    const uint32_t TEXTURE_VERTEX_COMPONENT_COUNT = 2;
    float positions[TRIANGLE_VERTEX_COUNT * (GEOMETRY_VERTEX_COMPONENT_COUNT + TEXTURE_VERTEX_COMPONENT_COUNT)] = {
        -.5f, -.5f,  .0f , .0f,
         .5f, -.5f, 1.0f,  .0f,
         .5f,  .5f, 1.0f, 1.0f,
        -.5f,  .5f,  .0f, 1.0f  
    };

    const uint32_t VBO_SIZE = sizeof(positions);

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, VBO_SIZE);
    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.push<GLfloat>(GEOMETRY_VERTEX_COMPONENT_COUNT);
    vertexBufferLayout.push<GLfloat>(TEXTURE_VERTEX_COMPONENT_COUNT);

    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    const uint32_t INDECIES_COUNT = 6;
    uint32_t indecies[INDECIES_COUNT] = {
       0, 1, 2,
       2, 3, 0
    };

    const uint32_t IBO_SIZE = sizeof(indecies);
    IndexBuffer indexBuffer(indecies, INDECIES_COUNT);

    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/textures/texture.png");

    shader.bind();
    texture.bind();

    shader.setUniform1i("u_texture", 0);

    float_t r = 0.0f;
    float_t g = 0.3f;
    float_t b = 0.9f;
    float_t i_r = 0.003f;
    float_t i_g = 0.003f;
    float_t i_b = 0.003f;

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        incrementColorValue(i_r, r);
        incrementColorValue(i_g, g);
        incrementColorValue(i_b, b);

        shader.setUniform4f("u_color", r, g, b, 1.0f);

        renderer.draw(vertexArray, indexBuffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}