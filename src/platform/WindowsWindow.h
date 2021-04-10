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
    WindowsWindow(
            const std::string &title,
            uint32_t width,
            uint32_t height,
            WindowEventsListener &windowCallback,
            ScrollEventsListener &scrollCallback
            );
    ~WindowsWindow() = default;

    void update() override;

    [[nodiscard]] GLFWwindow *getNativeWindow() const override { return m_window; }

    [[nodiscard]] uint32_t getWidth() const override { return m_width; }
    [[nodiscard]] uint32_t getHeight() const override { return m_height; }

private:
    GLFWwindow *m_window;

    const std::string &m_title;
    uint32_t m_width;
    uint32_t m_height;

    WindowEventsListener m_windowEventCallback;
    ScrollEventsListener m_scrollEventCallback;
private:
    void resize(int32_t width, int32_t height);
    void offsetZoom(int32_t offset);
};