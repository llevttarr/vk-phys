#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <GLFW/glfw3.h>

class Window{
public:

private:
    std::unique_ptr<GLFWwindow*> window;
};

#endif // WINDOW_HPP