#pragma once

#include <GLFW/glfw3.h>

class Game
{
public:
    static inline float DeltaTime;
    static void CalculateDeltaTime();

private:
    static inline float _previousFrameTime;
};