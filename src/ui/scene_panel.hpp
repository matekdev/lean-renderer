#pragma once

#include "render/frame_buffer.hpp"

class ScenePanel
{
public:
    ScenePanel();

    void Render();
    void Resize(int width, int height);

private:
    FrameBuffer _frameBuffer;
    int _width;
    int _height;
};