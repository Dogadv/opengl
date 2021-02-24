#include "../core/input/Input.h"

Input::Input(GLFWwindow *window)
: m_window(window) {}

bool Input::isKeyPressed(int32_t keycode)
{
    auto state = glfwGetKey(m_window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 Input::getMousePosition()
{
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);

    return { (float)x, (float)y };
}

bool Input::isMouseButtonPressed(int32_t button)
{
    auto state = glfwGetMouseButton(m_window, button);
    return state == GLFW_PRESS;
}


