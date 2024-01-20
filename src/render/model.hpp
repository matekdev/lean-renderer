#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader;

class Model
{
public:
    Model();

    glm::vec3 GetPosition();
    glm::vec3 GetRotation();

    void Draw(Shader &shader);
    void SetPosition(const glm::vec3 &pos);
    void SetRotation(const glm::vec3 &rot);

private:
    GLuint _vao;
    GLuint _vbo;
    glm::vec3 _position = glm::vec3(0.0f);
    glm::vec3 _rotation = glm::vec3(0.0f); // pitch, yaw, roll
};