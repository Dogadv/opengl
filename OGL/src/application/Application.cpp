#include <iostream>
#include <string>

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

    const uint32_t TRIANGLE_VERTEX_COUNT = 4;
    const uint32_t GEOMETRY_VERTEX_COMPONENT_COUNT = 2;
    const uint32_t TEXTURE_VERTEX_COMPONENT_COUNT = 2;
    const uint32_t COLOR_VERTEX_COMPONENT_COUNT = 4;
    const uint32_t TEXTURE_SLOT_VERTEX_COMPONENT_COUNT = 1;
    float positions[2 /* 2 objects */ * TRIANGLE_VERTEX_COUNT * (GEOMETRY_VERTEX_COMPONENT_COUNT + TEXTURE_VERTEX_COMPONENT_COUNT + COLOR_VERTEX_COMPONENT_COUNT + TEXTURE_SLOT_VERTEX_COMPONENT_COUNT)] = {
        /*  geometry  */  /* texture coord */  /*        color      */ /* texture id */
        -100.0f, -100.0f,      .0f , .0f,      0.0f, 1.0f, 0.0f, 1.0f,    0.0f,
         100.0f, -100.0f,     1.0f,  .0f,      0.0f, 1.0f, 0.0f, 1.0f,    0.0f,
         100.0f,  100.0f,     1.0f, 1.0f,      0.0f, 1.0f, 0.0f, 1.0f,    0.0f,
        -100.0f,  100.0f,      .0f, 1.0f,      0.0f, 1.0f, 0.0f, 1.0f,    0.0f,
                                                                          
         100.0f,  100.0f,      .0f , .0f,      1.0f, 0.0f, 0.0f, 1.0f,    1.0f,
         300.0f,  100.0f,     1.0f,  .0f,      1.0f, 0.0f, 0.0f, 1.0f,    1.0f,
         300.0f,  300.0f,     1.0f, 1.0f,      1.0f, 0.0f, 0.0f, 1.0f,    1.0f,
         100.0f,  300.0f,      .0f, 1.0f,      1.0f, 0.0f, 0.0f, 1.0f,    1.0f,
    };

    const uint32_t VBO_SIZE = sizeof(positions);

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(positions, VBO_SIZE);
    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.push<GLfloat>(GEOMETRY_VERTEX_COMPONENT_COUNT);
    vertexBufferLayout.push<GLfloat>(TEXTURE_VERTEX_COMPONENT_COUNT);
    vertexBufferLayout.push<GLfloat>(COLOR_VERTEX_COMPONENT_COUNT);
    vertexBufferLayout.push<GLfloat>(TEXTURE_SLOT_VERTEX_COMPONENT_COUNT);

    vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

    const uint32_t INDECIES_COUNT = 6 * 2;
    uint32_t indecies[INDECIES_COUNT] = {
       0,  1,  2,  2,  3,  0,
       4,  5,  6,  6,  7,  4
    };

    const uint32_t IBO_SIZE = sizeof(indecies);
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

    float zoom = 1.0f;

    while (renderer.isRunning())
    {
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.bind();
        shader.setUniformMat4f("u_mvp", renderer.getMVPMatrix(modelTranslation, cameraTranslation, zoom));

        renderer.draw(vertexArray, indexBuffer);
        
        {
            ImGui::Begin("params");
            ImGui::SliderFloat2("camera position", &cameraTranslation.x, 0, (float)width, "%g", 0);
            ImGui::SliderFloat("camera zoom", &zoom, .25f, 2.5f, "%g", 0);
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