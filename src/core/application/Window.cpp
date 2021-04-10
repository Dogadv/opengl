#include "../../pch.h"

#ifdef PLATFORM_WINDOWS
#include "../../platform/WindowsWindow.h"
#endif

std::unique_ptr<Window> Window::create(
        const std::string &title,
        uint32_t width,
        uint32_t height,
        WindowEventsListener& windowCallback,
        ScrollEventsListener& scrollCallback
        )
{
#ifdef PLATFORM_WINDOWS
    return std::make_unique<WindowsWindow>(title, width, height, windowCallback, scrollCallback);
#else
    static_assert("Unknown platform!");
    return nullptr;
#endif
}
