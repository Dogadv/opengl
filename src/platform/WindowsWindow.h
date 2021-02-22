#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../core/application/Window.h"

class WindowsWindow : public Window
{
public:
    WindowsWindow(const std::string &title, uint32_t width, uint32_t height);
    ~WindowsWindow() = default;

    virtual void update() override;

    [[nodiscard]] GLFWwindow *getNativeWindow() const override { return m_window; }

    [[nodiscard]] uint32_t getWidth() const override { return m_width; }
    [[nodiscard]] uint32_t getHeight() const override { return m_height; }

private:
    GLFWwindow *m_window;

    const std::string &m_title;
    const uint32_t m_width;
    const uint32_t m_height;
};