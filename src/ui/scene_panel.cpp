#include "scene_panel.hpp"

#include "log.hpp"
#include "math/math.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

ScenePanel::ScenePanel() : _frameBuffer(FrameBuffer()), _camera(Camera()), _shader(Shader("shaders/vs.vert", "shaders/fs.frag"))
{
    _gameObjects = {};
    _gameObjects.push_back(GameObject("models/hamster/hamster.obj"));
    _gameObjects.push_back(GameObject("models/hamster/hamster.obj"));
    _gameObjects.push_back(GameObject("models/hamster/hamster.obj"));
}

std::vector<GameObject> &ScenePanel::GetGameObjects()
{
    return _gameObjects;
}

GameObject *&ScenePanel::GetSelectedGameObject()
{
    return _selectedGameObject;
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

    if (_selectedGameObject)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(_viewPortBounds[0].x, _viewPortBounds[0].y, _viewPortBounds[1].x - _viewPortBounds[0].x, _viewPortBounds[1].y - _viewPortBounds[0].y);

        glm::mat4 transform = _selectedGameObject->GetTransform();
        ImGuizmo::Manipulate(glm::value_ptr(_camera.GetViewMatrix()), glm::value_ptr(_camera.GetProjectionMatrix()), _activeGizmo, ImGuizmo::WORLD, glm::value_ptr(transform), nullptr, nullptr, nullptr, nullptr);

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 position, rotation, scale;
            DecomposeTransform(transform, position, rotation, scale);

            glm::vec3 deltaRotation = rotation - _selectedGameObject->Rotation;
            _selectedGameObject->Position = position;
            _selectedGameObject->Rotation += deltaRotation;
            _selectedGameObject->Scale = scale;
        }
    }

    ImGui::End();
}

void ScenePanel::Input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
        DeleteSelectedGameObject();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        _selectedGameObject = nullptr;

    auto isUsingMouse = ImGuizmo::IsUsing() || _camera.IsMouseLocked();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !isUsingMouse)
        _activeGizmo = ImGuizmo::OPERATION::TRANSLATE;

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !isUsingMouse)
        _activeGizmo = ImGuizmo::OPERATION::ROTATE;

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !isUsingMouse)
        _activeGizmo = ImGuizmo::OPERATION::SCALE;
}

void ScenePanel::Resize(float width, float height)
{
    _width = width;
    _height = height;
    _frameBuffer.CreateBuffer(width, height);
}

void ScenePanel::DeleteSelectedGameObject()
{
    if (!_selectedGameObject)
        return;

    _gameObjects.erase(std::remove_if(_gameObjects.begin(), _gameObjects.end(),
                                      [&](const GameObject &m)
                                      { return _selectedGameObject == &m; }),
                       _gameObjects.end());
    _selectedGameObject = nullptr;
}
