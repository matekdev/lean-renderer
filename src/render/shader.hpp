#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    GLuint GetId();
    void SetMat4(const glm::mat4 &mat4, const std::string &name);

private:
    GLuint _id;

    GLuint CompileShader(GLenum shaderType, const std::string &shaderSource);
};