#include "window.hpp"

#include <glog/logging.h>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    auto window = Window(1400, 900, "Lean Renderer");
    window.Run();
}