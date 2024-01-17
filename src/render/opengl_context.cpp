#include "opengl_context.hpp"

#include "window.hpp"

OpenGLContext::OpenGLContext(Window *window) : _window(window)
{
    glfwMakeContextCurrent(_window->GetNativeWindow());
    gladLoadGL();
}

void OpenGLContext::PreRender()
{
}

void OpenGLContext::PostRender()
{
    glfwPollEvents();
    glfwSwapBuffers(_window->GetNativeWindow());
}

void OpenGLContext::Destroy()
{
    glfwDestroyWindow(_window->GetNativeWindow());
    glfwTerminate();
}