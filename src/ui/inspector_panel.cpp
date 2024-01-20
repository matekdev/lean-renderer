#include "inspector_panel.hpp"

#include "render/model.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

InspectorPanel::InspectorPanel()
{
}

void InspectorPanel::Render(Model *&selectedModel)
{
    ImGui::Begin("Inspector");

    if (selectedModel)
    {
        ImGui::Text("Model is selected");
    }

    ImGui::End();
}