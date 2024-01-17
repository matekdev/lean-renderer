#include "scene_panel.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ScenePanel::ScenePanel()
{
    _frameBuffer = FrameBuffer();
    Resize(800, 600);
}

void ScenePanel::Render()
{
    _frameBuffer.Bind();

    InternalRender();

    _frameBuffer.Unbind();

    ImGui::Begin("Scene");

    auto panelSize = ImGui::GetContentRegionAvail();
    if (panelSize.x != _width || panelSize.y != _height)
        Resize(panelSize.x, panelSize.y);

    uint64_t textureId = _frameBuffer.GetTextureId();
    ImGui::Image(reinterpret_cast<void *>(textureId), ImVec2{(float)_width, (float)_height}, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();
}

void ScenePanel::InternalRender()
{
    glClearColor(0.31f, 0.41f, 0.46f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ScenePanel::Resize(int width, int height)
{
    _width = width;
    _height = height;
    _frameBuffer.CreateBuffer(width, height);
}
