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

    for (auto &model : models)
    {
        if (ImGui::Selectable(model.Name.length() == 0 ? "<empty>" : model.Name.c_str(), selectedModel == &model))
        {
            selectedModel = &model;
        }
    }

    ImGui::End();
}
