#include "model.hpp"

#include "shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "log.hpp"

static float vertices[] = {
    // positions      // colors         // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

static unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

Model::Model()
{
    Name = "object " + std::to_string(_id++);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::string filePath = "models/container.jpg";
    int width, height, colorChannels;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &colorChannels, 0);
    if (!data)
    {
        LOG(ERROR) << "Failed to load texture: " << filePath;
        return;
    }

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Model::Draw(Shader &shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(glm::mat4(1.0f), Position);
    model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, Scale);

    shader.SetMat4(model, "model");
    glUseProgram(shader.GetId());
    glBindTexture(GL_TEXTURE_2D, _texture);
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
