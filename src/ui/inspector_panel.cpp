#include "inspector_panel.hpp"

#include "render/model.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
        ImGui::DragScalar("x", ImGuiDataType_Float, &position.x, 0.005f, &floatMin, &floatMax, "%f");
        ImGui::DragScalar("y", ImGuiDataType_Float, &position.y, 0.005f, &floatMin, &floatMax, "%f");
        ImGui::DragScalar("z", ImGuiDataType_Float, &position.z, 0.005f, &floatMin, &floatMax, "%f");
        selectedModel->SetPosition(position);
    }

    ImGui::End();
}