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
        auto floatMin = std::numeric_limits<float>::min();
        auto floatMax = -std::numeric_limits<float>::max();

        DrawVec3Control("Position", selectedGameObject->Position, 0.0f, 100.0f);
        DrawVec3Control("Rotation", selectedGameObject->Rotation, 0.0f, 100.0f);
        DrawVec3Control("Scale", selectedGameObject->Scale, 1.0f, 100.0f);
    }

    ImGui::End();
}