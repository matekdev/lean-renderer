#pragma once

struct Window;

class OpenGLContext
{
public:
    OpenGLContext(Window *window);
    void PreRender();
    void PostRender();
    void Destroy();

private:
    Window *_window;
};