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
    int ReadPixel(int x, int y);

private:
    GLuint _fbo;
    GLuint _rbo;
    GLuint _textureId;
    int _width;
    int _height;
};
