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

void InspectorPanel::Render(GameObject *&selectedModel)
{
    ImGui::Begin("Inspector");

    if (selectedModel)
    {
        ImGui::InputText("name", &selectedModel->Name);

        auto floatMin = std::numeric_limits<float>::min();
        auto floatMax = -std::numeric_limits<float>::max();

        ImGui::DragFloat3("position", glm::value_ptr(selectedModel->Position), 0.5f, floatMin, floatMax);
        ImGui::DragFloat3("rotation", glm::value_ptr(selectedModel->Rotation), 0.5f, -180.0f, 180.0f);
        ImGui::DragFloat3("scale", glm::value_ptr(selectedModel->Scale), 0.25f, 0.0f, floatMax);

        DrawVec3Control("position", selectedModel->Position, 0.0f, 100.0f);
    }

    ImGui::End();
}