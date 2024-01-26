#include "objects_panel.hpp"

#include "game.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

ObjectsPanel::ObjectsPanel()
{
}

void ObjectsPanel::Render()
{
    ImGui::Begin("Objects");

    for (auto &gameObject : Game::GameObjects)
    {
        if (ImGui::Selectable(gameObject.Name.c_str(), Game::SelectedGameObject == &gameObject))
        {
            Game::SelectedGameObject = &gameObject;
        }
    }

    ImGui::End();
}
