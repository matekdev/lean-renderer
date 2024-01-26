#pragma once

#include "render/frame_buffer.hpp"
#include "render/shader.hpp"
#include "render/camera.hpp"
#include "render/game_object/game_object.hpp"
#include "ui/components/gizmo.hpp"

#include <vector>

class ScenePanel
{
public:
    ScenePanel();

    void Render(GLFWwindow *window);
    void Input(GLFWwindow *window);
    void Resize(float width, float height);

private:
    glm::vec2 _viewPortBounds[2];
    float _width;
    float _height;
    FrameBuffer _frameBuffer;
    Camera _camera;
    Shader _shader;
    ImGuizmo::OPERATION _activeGizmo = ImGuizmo::OPERATION::TRANSLATE;
};