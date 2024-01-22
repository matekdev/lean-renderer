#include "shader.hpp"

#include "log.hpp"

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

void Shader::SetInt(int i, const std::string &name)
{
    GLint myLoc = glGetUniformLocation(GetId(), name.c_str());
    glUniform1i(myLoc, i);
}

void Shader::SetMat4(const glm::mat4 &mat4, const std::string &name)
{
    GLint myLoc = glGetUniformLocation(GetId(), name.c_str());
    glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
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

        LOG(ERROR) << "Compile error in shader: " << strInfoLog;
        delete[] strInfoLog;
    }

    return shaderId;
}
