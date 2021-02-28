#include <iostream>
#include <array>

#include "../core/buffer/vertex/VertexBuffer.h"
#include "../core/buffer/vertex/VertexArray.h"
#include "../core/buffer/index/IndexBuffer.h"

#include "../core/texture/Texture.h"
#include "../core/shader/Shader.h"
#include "../core/application/Application.h"

static std::array<Vertex, 4> buildQuad(const glm::vec2 &position, const GLuint textureIndex)
{
    GLfloat size = 1.0f;

    Vertex v0 = {{position.x, position.y}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, textureIndex};
    Vertex v1 = {{position.x + size, position.y}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, textureIndex};
    Vertex v2 = {{position.x + size, position.y + size}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, textureIndex};
    Vertex v3 = {{position.x, position.y + size}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, textureIndex};

    return {v0, v1, v2, v3};
}

int main()
{
    const uint32_t width = 1280;
    const uint32_t height = 720;

    OrthographicCamera orthoCamera((uint32_t) (width / 2), (uint32_t) (height / 2));
    Application application("Hello, OpenGL!", width, height, orthoCamera);
    Input &input = application.getInput();

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(sizeof(Vertex) * 1000);
    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.set<Vertex>();
    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    const GLuint INDICES_COUNT = 6 * 2;
    GLuint indices[INDICES_COUNT] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4
    };

    IndexBuffer indexBuffer(indices, INDICES_COUNT);

    Shader shader("shaders/Basic.shader");
    Texture oglTexture("textures/texture.png", 0);
    Texture cobblestoneTexture("textures/cobblestone.png", 1);

    shader.bind();
    oglTexture.bind();
    cobblestoneTexture.bind();

    GLint samplers[2] =
            {
                    oglTexture.getSlotIndex(),
                    cobblestoneTexture.getSlotIndex()
            };

    shader.setUniform1iv("u_textures", samplers);

    glm::vec3 cameraTranslation(5.0f, 2.5f, 0.0);
    glm::vec3 modelTranslation(0.0f, 0.0f, 0.0f);

    glm::vec2 q0Translation(0.0f, 0.0f);
    glm::vec2 q1Translation(1.0f, 1.0f);

    float cameraSpeed = 0.05f;

    while (application.isRunning())
    {
        application.clear();

        auto q0 = buildQuad(q0Translation, 0);
        auto q1 = buildQuad(q1Translation, 1);

        Vertex vertices[8];

        memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
        memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

        vertexBuffer.bind(vertices, sizeof(vertices));

        shader.bind();
        oglTexture.bind();
        cobblestoneTexture.bind();
        shader.setUniformMat4f("u_mvp", application.getMVPMatrix(modelTranslation));

        application.draw(vertexArray, indexBuffer);

        if (input.isKeyPressed(GLFW_KEY_W)) orthoCamera.moveBy(glm::vec3(0.0, -cameraSpeed, 0.0));
        if (input.isKeyPressed(GLFW_KEY_A)) orthoCamera.moveBy(glm::vec3(cameraSpeed, 0.0, 0.0));
        if (input.isKeyPressed(GLFW_KEY_S)) orthoCamera.moveBy(glm::vec3(0.0, cameraSpeed, 0.0));
        if (input.isKeyPressed(GLFW_KEY_D)) orthoCamera.moveBy(glm::vec3(-cameraSpeed, 0.0, 0.0));

        application.update();
    }

    application.shutdown();
    return 0;
}