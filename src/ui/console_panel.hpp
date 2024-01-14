#pragma once

#include <string>
#include <vector>

#include <glog/logging.h>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class ConsolePanel : public google::LogSink
{
public:
    ConsolePanel();

    void Render();
    void send(google::LogSeverity severity, const char *full_filename,
              const char *base_filename, int line,
              const struct ::tm *tm_time,
              const char *message, size_t message_len) override;

private:
    const std::string INFO = "[INFO] ";
    const std::string WARNING = "[WARNING] ";
    const std::string ERROR = "[ERROR] ";

    std::string _input;
    std::vector<std::string> _previousLogs;

    ImVector<const char *> Commands;
    ImVector<char *> History;
    int HistoryPos; // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter Filter;
    bool _scrollToBottom;

    void ExecuteCommand(const std::string &command);
    std::string SeversityToString(google::LogSeverity severity);
};
