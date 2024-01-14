#include "console_panel.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ConsolePanel::ConsolePanel() {}

void ConsolePanel::Render()
{
    ImGui::Begin("Console");

    ImGui::End();
}
