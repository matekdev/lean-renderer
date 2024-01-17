#include "opengl_context.hpp"

#include "window.hpp"

OpenGLContext::OpenGLContext(Window *window) : _window(window)
{
}

void OpenGLContext::PreRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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