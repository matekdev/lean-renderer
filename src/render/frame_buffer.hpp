#pragma once

#include <glad/glad.h>

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

private:
    GLuint _fbo;
    GLuint _textureId;
    GLuint _depthId;
    int _width;
    int _height;
};
