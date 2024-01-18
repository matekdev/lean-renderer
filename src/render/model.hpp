#pragma once

#include <glad/glad.h>

class Shader;

class Model
{
public:
    Model();

    void Draw(Shader &shader);

private:
    GLuint _vao;
    GLuint _vbo;
};