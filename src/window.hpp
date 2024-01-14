#pragma once

#include "render/opengl_context.hpp"
#include "render/ui_context.hpp"

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    void Run();
    GLFWwindow *GetNativeWindow();
    int GetWidth();
    int GetHeight();

private:
    GLFWwindow *_glfwWindow;
    std::unique_ptr<OpenGLContext> _glContext;
    std::unique_ptr<UIContext> _uiContext;

    int _width;
    int _height;
};