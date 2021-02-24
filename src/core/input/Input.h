#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Input
{
public:
    Input(GLFWwindow *m_window);

    bool isKeyPressed(int32_t keycode);
    bool isMouseButtonPressed(int32_t button);
    glm::vec2 getMousePosition();

private:
    GLFWwindow *m_window;
};