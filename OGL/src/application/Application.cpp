#include <iostream>
#include <string>
#include <array>

#include "../entity/Vertex.h"

#include "../buffer/vertex/VertexBuffer.h"
#include "../buffer/vertex/VertexArray.h"
#include "../buffer/index/IndexBuffer.h"

#include "../texture/Texture.h"
#include "../shader/Shader.h"
#include "../core/Renderer.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

const char* glsl_version = "#version 130";

static std::array<Vertex, 4> buildQuad(const glm::vec2& position, const GLuint textureIndex)
{
    GLfloat size = 100.0f;

    Vertex v0 = { { position.x,        position.y        }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f ,0.0f }, textureIndex };
    Vertex v1 = { { position.x + size, position.y        }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, textureIndex };
    Vertex v2 = { { position.x + size, position.y + size }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, textureIndex };
    Vertex v3 = { { position.x,        position.y + size }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, textureIndex };

    return { v0, v1, v2, v3 };
}

int main(void)
{
    const uint32_t width = 1280;
    const uint32_t height = 720;

    Renderer renderer("Hello, OpenGL!", width, height);
    GLFWwindow* window = renderer.getWindow();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    const int verteciesCount = 8;

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(sizeof(Vertex) * 8);
    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.push<GLfloat>(VERTEX_POSITION_COMPONENT_COUNT);
    vertexBufferLayout.push<GLfloat>(VERTEX_COLOR_COMPONENT_COUNT);
    vertexBufferLayout.push<GLfloat>(VERTEX_TEXTURE_COORD_COMPONENT_COUNT);
    vertexBufferLayout.push<GLuint>(VERTEX_TEXTURE_INDEX_COMPONENT_COUNT);

    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    const GLuint INDECIES_COUNT = 6 * 2;
    GLuint indecies[INDECIES_COUNT] = {
       0,  1,  2,  2,  3,  0,
       4,  5,  6,  6,  7,  4
    };

    const GLuint IBO_SIZE = sizeof(indecies);
    IndexBuffer indexBuffer(indecies, INDECIES_COUNT);

    Shader shader("res/shaders/Basic.shader");
    Texture oglTexture("res/textures/texture.png", 0);
    Texture cobblestoneTexture("res/textures/cobblestone.png", 1);

    shader.bind();
    oglTexture.bind();
    cobblestoneTexture.bind();

    GLint samplers[2] = 
    { 
        oglTexture.getSlotIndex(),
        cobblestoneTexture.getSlotIndex()
    };

    shader.setUniform1iv("u_textures", samplers);

    glm::vec3 cameraTranslation(500.0f, 250.0f, 0.0);
    glm::vec3 modelTranslation(0.0f, 0.0f, 0.0f);

    glm::vec2 q0Translation(0.0f, 0.0f);
    glm::vec2 q1Translation(100.0f, 100.0f);

    GLfloat zoom = 1.0f;


    while (renderer.isRunning())
    {
        auto q0 = buildQuad(q0Translation, 0);
        auto q1 = buildQuad(q1Translation, 1);

        Vertex verticies[8];

        memcpy(verticies, q0.data(), q0.size() * sizeof(Vertex));
        memcpy(verticies + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

        vertexBuffer.bind(verticies, sizeof(verticies));

        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.bind();
        oglTexture.bind();
        cobblestoneTexture.bind();
        shader.setUniformMat4f("u_mvp", renderer.getMVPMatrix(modelTranslation, cameraTranslation, zoom));

        renderer.draw(vertexArray, indexBuffer);
        
        {
            ImGui::Begin("params");
            ImGui::SliderFloat2("camera position", &cameraTranslation.x, 0, (float)width, "%g", 0);
            ImGui::SliderFloat("camera zoom", &zoom, .25f, 2.5f, "%g", 0);
            ImGui::SliderFloat2("object 1 position", &q0Translation.x, 0, (float)width, "%g", 0);
            ImGui::SliderFloat2("object 2 position", &q1Translation.x, 0, (float)width, "%g", 0);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer.update();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}