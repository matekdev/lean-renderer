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
    void Input(GLFWwindow *window);
    void Resize(int width, int height);

    std::vector<Model> &GetModels();
    Model *&GetSelectedModel();

private:
    int _width;
    int _height;
    FrameBuffer _frameBuffer;
    Camera _camera;
    Shader _shader;

    Model *_selectedModel = nullptr;
    std::vector<Model> _models;
};