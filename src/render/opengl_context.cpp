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
    glfwSwapBuffers(_window->GetNativeWindow());
    glfwPollEvents();
}

void OpenGLContext::Destroy()
{
    glfwDestroyWindow(_window->GetNativeWindow());
    glfwTerminate();
}