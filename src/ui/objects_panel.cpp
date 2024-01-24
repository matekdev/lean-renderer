#include "objects_panel.hpp"

#include "render/game_object/game_object.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

ObjectsPanel::ObjectsPanel()
{
}

void ObjectsPanel::Render(std::vector<GameObject> &gameObjects, GameObject *&selectedGameObject)
{
    ImGui::Begin("Objects");

    for (auto &gameObject : gameObjects)
    {
        if (ImGui::Selectable(gameObject.Name.c_str(), selectedGameObject == &gameObject))
        {
            selectedGameObject = &gameObject;
        }
    }

    ImGui::End();
}
