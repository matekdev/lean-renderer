#include "objects_panel.hpp"

#include "render/model.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

ObjectsPanel::ObjectsPanel()
{
}

void ObjectsPanel::Render(std::vector<Model> &models, Model *&selectedModel)
{
    ImGui::Begin("Objects");

    for (int i = 0; i < models.size(); i++)
    {
        std::string name = "model " + std::to_string(i);
        if (ImGui::Selectable(name.c_str(), selectedModel == &models[i]))
        {
            selectedModel = &models[i];
        }
    }

    ImGui::End();
}
