#pragma once

#include "render/frame_buffer.hpp"
#include "render/model.hpp"
#include "render/shader.hpp"

class ScenePanel
{
public:
    ScenePanel();

    void Render();
    void Resize(int width, int height);

private:
    int _width;
    int _height;
    FrameBuffer _frameBuffer;
    Model _model;
    Shader _shader;

    void InternalRender();
};