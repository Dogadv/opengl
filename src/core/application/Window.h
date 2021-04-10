#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>
#include <functional>

enum class WindowEvents
{
    OnResize,
    OnClose
};

// Temporary solution until I find out something wiser
enum class ScrollEvents
{
    OnScrollUp,
    OnScrollDown
};

typedef std::function<void(WindowEvents)> WindowEventsListener;
typedef std::function<void(ScrollEvents)> ScrollEventsListener;

class Window
{
public:
    virtual ~Window() = default;

    virtual void update() = 0;

    [[nodiscard]] virtual GLFWwindow *getNativeWindow() const = 0;

    [[nodiscard]] virtual uint32_t getWidth() const = 0;
    [[nodiscard]] virtual uint32_t getHeight() const = 0;

    static std::unique_ptr<Window> create(
            const std::string &title,
            uint32_t width,
            uint32_t height,
            WindowEventsListener& windowCallback,
            ScrollEventsListener& scrollCallback
            );
};