#include "window.hpp"

Window::Window(int width, int height, const std::string &windowTitle) : _width(width), _height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _glfwWindow = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    if (!_glfwWindow)
        throw std::runtime_error("Failed to create GLFW Window.");

    _glContext = std::make_unique<OpenGLContext>(this);
}

Window::~Window()
{
    _glContext->Destroy();
}

void Window::Run()
{
    while (!glfwWindowShouldClose(_glfwWindow))
    {
        _glContext->PreRender();

        _glContext->PostRender();
    }
}

GLFWwindow *Window::GetNativeWindow()
{
    return _glfwWindow;
}

int Window::GetWidth()
{
    return _width;
}

int Window::GetHeight()
{
    return _height;
}