#pragma once

#include "render/frame_buffer.hpp"
#include "render/shader.hpp"
#include "render/camera.hpp"
#include "render/game_object/game_object.hpp"

#include <vector>

class ScenePanel
{
public:
    ScenePanel();

    void Render(GLFWwindow *window);
    void Input(GLFWwindow *window);
    void Resize(float width, float height);

    std::vector<GameObject> &GetGameObjects();
    GameObject *&GetSelectedGameObject();

private:
    glm::vec2 _viewPortBounds[2];
    float _width;
    float _height;
    FrameBuffer _frameBuffer;
    Camera _camera;
    Shader _shader;

    GameObject *_selectedGameObject = nullptr;
    std::vector<GameObject> _gameObjects;
};