#include "objects_panel.hpp"

#include "render/model.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ObjectsPanel::ObjectsPanel()
{
}

void ObjectsPanel::Render(std::vector<Model> &models)
{
    ImGui::Begin("Objects");

    static int selected = -1;
    for (int i = 0; i < models.size(); i++)
    {
        if (ImGui::Selectable("cube", selected == i))
            selected = i;
    }

    ImGui::End();
}
