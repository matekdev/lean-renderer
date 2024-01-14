#include "opengl_context.hpp"

#include "window.hpp"

OpenGLContext::OpenGLContext(Window *window) : _window(window)
{
    glfwMakeContextCurrent(_window->GetNativeWindow());
    gladLoadGL();
}

void OpenGLContext::PreRender()
{
    glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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