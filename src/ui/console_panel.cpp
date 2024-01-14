#include "console_panel.hpp"

ConsolePanel::ConsolePanel() {}

void ConsolePanel::Render()
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("Console");

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::BeginPopupContextWindow())
    {
        // if (ImGui::Selectable("Clear"))
        //     ClearLog();
        ImGui::EndPopup();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    for (const auto &command : _previousCommands)
    {
        ImVec4 color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
        ImGui::TextUnformatted(command.c_str());
    }

    if (_scrollToBottom || (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
        ImGui::SetScrollHereY(1.0f);
    _scrollToBottom = false;

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Separator();

    // Command-line
    ImGui::PushItemWidth(-1);
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText("##label", &_input, input_text_flags))
        ExecuteCommand(_input);

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::End();
}

void ConsolePanel::ExecuteCommand(const std::string &command)
{
    AddLog(command);

    _input = "";
    _scrollToBottom = true;
}

void ConsolePanel::AddLog(const std::string &log)
{
    _previousCommands.push_back(log);
}