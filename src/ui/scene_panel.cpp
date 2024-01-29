#include "scene_panel.hpp"

#include "log.hpp"
#include "game.hpp"
#include "math/math.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

ScenePanel::ScenePanel() : _frameBuffer(FrameBuffer()), _pickingBuffer(FrameBuffer()), _camera(Camera()), _modelShader(Shader("shaders/model.vert", "shaders/model.frag")), _pickingShader(Shader("shaders/picking.vert", "shaders/picking.frag"))
{
    Game::GameObjects.push_back(GameObject("models/icosphere/icosphere.obj"));
    Game::GameObjects.push_back(GameObject("models/hamster/hamster.obj"));
    Game::GameObjects.push_back(GameObject("models/cube/cube.obj"));
}

void ScenePanel::Render(GLFWwindow *window)
{
    ImGui::ShowDemoWindow();

    PickingPass();
    RenderPass();

    ImGui::Begin("Scene");

    auto panelSize = ImGui::GetContentRegionAvail();
    if (panelSize.x != _width || panelSize.y != _height)
        Resize(panelSize.x, panelSize.y);

    uint64_t textureId = _frameBuffer.GetTextureId();
    ImGui::Image(reinterpret_cast<void *>(textureId), ImVec2{_width, _height}, ImVec2{0, 1}, ImVec2{1, 0});

    _camera.Input(panelSize.x, panelSize.y, window, ImGui::IsWindowHovered());
    _camera.Update(panelSize.x, panelSize.y);

    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    _viewPortBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
    _viewPortBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};

    if (Game::SelectedGameObject)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(_viewPortBounds[0].x, _viewPortBounds[0].y, _viewPortBounds[1].x - _viewPortBounds[0].x, _viewPortBounds[1].y - _viewPortBounds[0].y);

        glm::mat4 transform = Game::SelectedGameObject->GetTransform();
        ImGuizmo::Manipulate(glm::value_ptr(_camera.GetViewMatrix()), glm::value_ptr(_camera.GetProjectionMatrix()), _activeGizmo, ImGuizmo::WORLD, glm::value_ptr(transform), nullptr, nullptr, nullptr, nullptr);

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 position, rotation, scale;
            DecomposeTransform(transform, position, rotation, scale);

            glm::vec3 deltaRotation = rotation - Game::SelectedGameObject->Rotation;
            Game::SelectedGameObject->Position = position;
            Game::SelectedGameObject->Rotation += deltaRotation;
            Game::SelectedGameObject->Scale = scale;
        }
    }

    ImGui::End();
}

void ScenePanel::PickingPass()
{
    // This is actually a horrible way to handle picking because we are essentially rendering everything twice.
    // The first time rendering all objects with a unique color, and the second time to render the actual scene.
    _pickingBuffer.Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < Game::GameObjects.size(); ++i)
    {
        auto &gameObject = Game::GameObjects[i];
        gameObject.Render(_pickingShader);

        int r = (i & 0x000000FF) >> 0;
        int g = (i & 0x0000FF00) >> 8;
        int b = (i & 0x00FF0000) >> 16;

        GLint myLoc = glGetUniformLocation(_pickingShader.GetId(), "PickingColor");
        glUniform4fv(myLoc, 1, glm::value_ptr(glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f)));
    }

    _pickingShader.SetMat4(_camera.GetViewProjectionMatrix(), "CameraMatrix");

    LOG(INFO) << _pickingBuffer.ReadPixel(0, 0);

    _pickingBuffer.Unbind();
}

void ScenePanel::RenderPass()
{
    _frameBuffer.Bind();

    glClearColor(0.31f, 0.41f, 0.46f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < Game::GameObjects.size(); ++i)
    {
        auto &gameObject = Game::GameObjects[i];
        gameObject.Render(_modelShader);
    }

    _modelShader.SetMat4(_camera.GetViewProjectionMatrix(), "CameraMatrix");
    _frameBuffer.Unbind();
}

void ScenePanel::Input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Game::SelectedGameObject = nullptr;

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
    _pickingBuffer.CreateBuffer(width, height);
}
