#include "scene_panel.hpp"

#include "log.hpp"
#include "ui/components/gizmo.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

ScenePanel::ScenePanel() : _frameBuffer(FrameBuffer()), _camera(Camera()), _shader(Shader("shaders/vs.vert", "shaders/fs.frag"))
{
    _gameObjects = {};
    _gameObjects.push_back(GameObject("models/hamster/hamster.obj"));
    _gameObjects.push_back(GameObject("models/hamster/hamster.obj"));
    _gameObjects.push_back(GameObject("models/hamster/hamster.obj"));
}

void ScenePanel::Render(GLFWwindow *window)
{
    ImGui::ShowDemoWindow();

    _frameBuffer.Bind();

    glClearColor(0.31f, 0.41f, 0.46f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &gameObject : _gameObjects)
    {
        gameObject.Render(_shader);
    }

    _frameBuffer.Unbind();

    ImGui::Begin("Scene");

    auto panelSize = ImGui::GetContentRegionAvail();
    if (panelSize.x != _width || panelSize.y != _height)
        Resize(panelSize.x, panelSize.y);

    uint64_t textureId = _frameBuffer.GetTextureId();
    ImGui::Image(reinterpret_cast<void *>(textureId), ImVec2{_width, _height}, ImVec2{0, 1}, ImVec2{1, 0});

    _camera.Input(panelSize.x, panelSize.y, window, ImGui::IsWindowHovered());
    _camera.Update(panelSize.x, panelSize.y, _shader);

    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    _viewPortBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
    _viewPortBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};

    if (_selectedGameObject != nullptr)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(_viewPortBounds[0].x, _viewPortBounds[0].y, _viewPortBounds[1].x - _viewPortBounds[0].x, _viewPortBounds[1].y - _viewPortBounds[0].y);

        glm::mat4 transform = _selectedGameObject->GetTransform();
        ImGuizmo::Manipulate(glm::value_ptr(_camera.GetViewMatrix()), glm::value_ptr(_camera.GetProjectionMatrix()), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, nullptr);
    }

    ImGui::End();
}

void ScenePanel::Input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
    {
        if (_selectedGameObject)
        {
            _gameObjects.erase(std::remove_if(
                                   _gameObjects.begin(),
                                   _gameObjects.end(),
                                   [&](const GameObject &m)
                                   { return _selectedGameObject == &m; }),
                               _gameObjects.end());
            _selectedGameObject = nullptr;
        }
    }
}

void ScenePanel::Resize(float width, float height)
{
    _width = width;
    _height = height;
    _frameBuffer.CreateBuffer(width, height);
}

std::vector<GameObject> &ScenePanel::GetGameObjects()
{
    return _gameObjects;
}

GameObject *&ScenePanel::GetSelectedGameObject()
{
    return _selectedGameObject;
}