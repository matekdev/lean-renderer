#include "frame_buffer.hpp"

FrameBuffer::FrameBuffer() : _fbo{0}, _textureId{0}, _depthId{0}, _width{0}, _height{0} {}

FrameBuffer::~FrameBuffer()
{
    DeleteBuffer();
}

void FrameBuffer::CreateBuffer(int width, int height)
{
    _width = width;
    _height = height;

    if (_fbo)
        DeleteBuffer();

    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glCreateTextures(GL_TEXTURE_2D, 1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &_depthId);
    glBindTexture(GL_TEXTURE_2D, _depthId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthId, 0);

    GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(_textureId, buffers);

    Unbind();
}

void FrameBuffer::DeleteBuffer()
{
    if (!_fbo)
        return;

    glDeleteTextures(1, &_textureId);
    glDeleteTextures(1, &_depthId);
    glDeleteFramebuffers(GL_FRAMEBUFFER, &_fbo);
    _textureId = 0;
    _depthId = 0;
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
