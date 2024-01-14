#include <glog/logging.h>
#include "window.hpp"

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

    auto window = Window(1024, 720, "LEAN RENDERER");
    window.Run();
}