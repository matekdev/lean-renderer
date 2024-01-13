#include "shader.hpp"

#include <fstream>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    std::ifstream is_vs(vertexShaderPath.data());
    const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

    std::ifstream is_fs(fragmentShaderPath.data());
    const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());

    _id = glCreateProgram();

    auto vs = CompileShader(GL_VERTEX_SHADER, f_vs);
    auto fs = CompileShader(GL_FRAGMENT_SHADER, f_fs);

    glAttachShader(_id, vs);
    glAttachShader(_id, fs);

    glLinkProgram(_id);
    glValidateProgram(_id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

GLuint Shader::GetId()
{
    return _id;
}

GLuint Shader::CompileShader(GLenum shaderType, const std::string &shaderSource)
{
    auto shaderId = glCreateShader(shaderType);

    const char *c_source = shaderSource.c_str();
    glShaderSource(shaderId, 1, &c_source, nullptr);
    glCompileShader(shaderId);

    GLint result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        GLchar *strInfoLog = new GLchar[length + 1];
        glGetShaderInfoLog(shaderId, length, &length, strInfoLog);

        fprintf(stderr, "Compile error in shader: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    return shaderId;
}
