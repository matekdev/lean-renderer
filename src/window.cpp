#include "window.hpp"

#include "game.hpp"

Window::Window(int width, int height, const std::string &windowTitle) : _width(width), _height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    _glfwWindow = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    if (!_glfwWindow)
        throw std::runtime_error("Failed to create GLFW Window.");

    glfwSetWindowUserPointer(_glfwWindow, this);
    glfwMakeContextCurrent(_glfwWindow);
    gladLoadGL();

    _glContext = std::make_unique<OpenGLContext>(this);
    _uiContext = std::make_unique<UIContext>(this);

    _scenePanel = std::make_unique<ScenePanel>();
    _consolePanel = std::make_unique<ConsolePanel>();
}

Window::~Window()
{
    _uiContext->Destroy();
    _glContext->Destroy();
}

void Window::Run()
{
    while (!glfwWindowShouldClose(_glfwWindow))
    {
        Game::CalculateDeltaTime();

        _glContext->PreRender();
        _uiContext->PreRender();

        _scenePanel->Render(GetNativeWindow());
        _consolePanel->Render();

        _uiContext->PostRender();
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
