#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader;

class Model
{
public:
    Model();

    void Draw(Shader &shader);
    void SetPosition(const glm::vec3 &pos);
    glm::vec3 GetPosition();

private:
    GLuint _vao;
    GLuint _vbo;
    glm::vec3 _position = glm::vec3(0.0f);
};