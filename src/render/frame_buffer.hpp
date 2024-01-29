#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void CreateBuffer(int width, int height);
    void DeleteBuffer();
    void Bind();
    void Unbind();
    GLuint GetTextureId();
    glm::vec3 EncodeIndex(int index);
    int DecodePixel(int x, int y);

private:
    GLuint _fbo;
    GLuint _rbo;
    GLuint _textureId;
    int _width;
    int _height;
};
