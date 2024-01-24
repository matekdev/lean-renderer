#include "inspector_panel.hpp"

#include "render/game_object/game_object.hpp"
#include "components/vec3_control.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/gtc/type_ptr.hpp>
#include <limits>

InspectorPanel::InspectorPanel()
{
}

void InspectorPanel::Render(GameObject *&selectedGameObject)
{
    ImGui::Begin("Inspector");

    if (selectedGameObject)
    {
        ImGui::InputText("name", &selectedGameObject->Name);

        auto floatMin = std::numeric_limits<float>::min();
        auto floatMax = -std::numeric_limits<float>::max();

        ImGui::DragFloat3("position", glm::value_ptr(selectedGameObject->Position), 0.5f, floatMin, floatMax);
        ImGui::DragFloat3("rotation", glm::value_ptr(selectedGameObject->Rotation), 0.5f, -180.0f, 180.0f);
        ImGui::DragFloat3("scale", glm::value_ptr(selectedGameObject->Scale), 0.25f, 0.0f, floatMax);

        DrawVec3Control("position", selectedGameObject->Position, 0.0f, 100.0f);
    }

    ImGui::End();
}