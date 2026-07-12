#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <GLFW/glfw3.h>

#include "wrenderer.hpp"

class Window{
public:
    class WBuilder;
private:
    Window();

    std::unique_ptr<GLFWwindow*> window;
};

class Window::WBuilder{
public:
    Window build() const{
        return Window();
    }
private:
};

#endif // WINDOW_HPP