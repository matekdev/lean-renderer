#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader;

class Model
{
public:
    Model();

    std::string Name;
    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f); // pitch, yaw, roll?
    glm::vec3 Scale = glm::vec3(1.0f);

    void Draw(Shader &shader);

private:
    inline static int _id;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _texture;
};