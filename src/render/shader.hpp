#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
    inline static const std::string MODEL_COLOR = "ModelColor";
    inline static const std::string LIGHT_COLOR = "LightColor";
    inline static const std::string LIGHT_POSITION = "LightPosition";
    inline static const std::string HAS_TEXTURE = "HasTexture";

    inline static const std::string PICKING_COLOR = "PickingColor";

    inline static const std::string MODEL_MATRIX = "ModelMatrix";
    inline static const std::string CAMERA_MATRIX = "CameraMatrix";

    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    GLuint GetId();
    void Bind();
    void SetInt(int i, const std::string &name);
    void SetBool(bool b, const std::string &name);
    void SetVec3(const glm::vec3 &vec3, const std::string &name);
    void SetVec4(const glm::vec3 &vec4, const std::string &name);
    void SetMat4(const glm::mat4 &mat4, const std::string &name);

private:
    GLuint _id;

    GLuint CompileShader(GLenum shaderType, const std::string &shaderSource);
};