#pragma once

#include "render/frame_buffer.hpp"
#include "render/model.hpp"
#include "render/shader.hpp"
#include "render/camera.hpp"

#include <vector>

class ScenePanel
{
public:
    ScenePanel();

    void Render(GLFWwindow *window);
    void Resize(int width, int height);

    std::vector<Model> &GetModels();

private:
    int _width;
    int _height;
    FrameBuffer _frameBuffer;
    Camera _camera;
    Model _model;
    Shader _shader;
    std::vector<Model> _models;
};