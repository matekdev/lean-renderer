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
        ImGui::InputText("name", &selectedModel->Name);

        auto floatMin = std::numeric_limits<float>::min();
        auto floatMax = -std::numeric_limits<float>::max();

        ImGui::DragFloat3("position", glm::value_ptr(selectedModel->Position), 0.5f, floatMin, floatMax);
        ImGui::DragFloat3("rotation", glm::value_ptr(selectedModel->Rotation), 0.5f, -180.0f, 180.0f);
    }

    ImGui::End();
}