#include "camera.hpp"

Camera::Camera()
{
}

void Camera::UpdateMatrix(int width, int height, Shader &shader)
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    viewMatrix = glm::lookAt(_position, _position + ORIENTATION, UP);
    projectionMatrix = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);

    shader.SetMat4(projectionMatrix * viewMatrix, "cameraMatrix");
}
