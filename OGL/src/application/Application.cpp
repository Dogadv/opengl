#include <iostream>
#include <string>

#include "../buffer/vertex/VertexBuffer.h"
#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"
#include "../texture/Texture.h"
#include "../shader/Shader.h"
#include "../core/Renderer.h"

int main(void)
{
    const uint32_t width = 640;
    const uint32_t height = 360;

    Renderer renderer("Hello, OpenGL!", width, height);

    const uint32_t TRIANGLE_VERTEX_COUNT = 4;
    const uint32_t GEOMETRY_VERTEX_COMPONENT_COUNT = 2;
    const uint32_t TEXTURE_VERTEX_COMPONENT_COUNT = 2;
    float positions[TRIANGLE_VERTEX_COUNT * (GEOMETRY_VERTEX_COMPONENT_COUNT + TEXTURE_VERTEX_COMPONENT_COUNT)] = {
        -100.0f, -100.0f,  .0f , .0f,
         100.0f, -100.0f, 1.0f,  .0f,
         100.0f,  100.0f, 1.0f, 1.0f,
        -100.0f,  100.0f,  .0f, 1.0f
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

    glm::vec3 cameraTranslation(0, 0, 0);
    glm::vec3 objectFooTranslation(100, 50, 0);
    glm::vec3 objectBarTranslation(200, 150, 0);

    while (renderer.isRunning())
    {
        renderer.clear();

        { // Object Foo
            shader.bind();
            shader.setUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);
            shader.setUniformMat4f("u_mvp", renderer.getMVPMatrix(objectFooTranslation, cameraTranslation));

            renderer.draw(vertexArray, indexBuffer);
        }
        
        { // Object Bar
            shader.bind();
            shader.setUniform4f("u_color", 0.0f, 0.0f, 1.0f, 1.0f);
            shader.setUniformMat4f("u_mvp", renderer.getMVPMatrix(objectBarTranslation, cameraTranslation));

            renderer.draw(vertexArray, indexBuffer);
        }
    }

    glfwTerminate();
    return 0;
}