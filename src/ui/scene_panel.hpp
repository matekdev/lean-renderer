#pragma once

#include "render/frame_buffer.hpp"
#include "render/model.hpp"
#include "render/shader.hpp"
#include "render/camera.hpp"

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
    Camera _camera;
    Model _model;
    Shader _shader;
};