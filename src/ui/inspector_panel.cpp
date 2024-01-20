#include "inspector_panel.hpp"

#include "render/model.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/gtc/type_ptr.hpp>
#include <limits>

InspectorPanel::InspectorPanel()
{
}

void InspectorPanel::Render(Model *&selectedModel)
{
    ImGui::Begin("Inspector");

    if (selectedModel)
    {
        auto floatMin = std::numeric_limits<float>::min();
        auto floatMax = -std::numeric_limits<float>::max();

        auto position = selectedModel->GetPosition();
        ImGui::DragFloat3("position", glm::value_ptr(position), 0.5f, floatMin, floatMax);
        selectedModel->SetPosition(position);

        auto rotation = selectedModel->GetRotation();
        ImGui::DragFloat3("rotation", glm::value_ptr(rotation), 0.5f, -180.0f, 180.0f);
        selectedModel->SetRotation(rotation);
    }

    ImGui::End();
}