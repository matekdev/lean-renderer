#include "frame_buffer.hpp"

#include <array>

FrameBuffer::FrameBuffer() : _fbo{0}, _rbo{0}, _textureId{0}, _width{0}, _height{0} {}

void FrameBuffer::CreateBuffer(int width, int height)
{
    _width = width;
    _height = height;

    if (_fbo)
        DeleteBuffer();

    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);

    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    Unbind();
}

FrameBuffer::~FrameBuffer()
{
    DeleteBuffer();
}

void FrameBuffer::DeleteBuffer()
{
    if (!_fbo)
        return;

    glDeleteFramebuffers(1, &_fbo);
    glDeleteTextures(1, &_textureId);
    glDeleteRenderbuffers(1, &_rbo);
}

void FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glViewport(0, 0, _width, _height);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer::GetTextureId()
{
    return _textureId;
}

// Make sure to bind this frame buffer before calling this.
int FrameBuffer::ReadPixel(int x, int y)
{
    std::array<unsigned char, 4> data;
    glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    int id = data[0] + data[1] * 256 + data[2] * 256 * 256;
    return id != 0x00ffffff ? id : -1;
}
