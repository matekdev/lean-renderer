#pragma once

#include <glad/glad.h>
#include <string>

struct Texture
{
    GLuint Id;
    std::string Type;
    std::string Path;
};