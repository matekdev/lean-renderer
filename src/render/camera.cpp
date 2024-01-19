#include "camera.hpp"

#include <GLFW/glfw3.h>

Camera::Camera()
{
}

void Camera::Update(int width, int height, Shader &shader)
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    viewMatrix = glm::lookAt(_position, _position + _orientation, UP);
    projectionMatrix = glm::perspective(glm::radians(90.0f), (float)(width / height), 0.1f, 100.0f);

    shader.SetMat4(projectionMatrix * viewMatrix, "cameraMatrix");
}

void Camera::Input(GLFWwindow *window, bool isWindowHovered)
{
    // If right click is down and we are hovering the scene panel, we want to lock the cursor to the window.
    auto isRightClickDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    if (!_isMouseLocked)
        _isMouseLocked = isRightClickDown && isWindowHovered;

    // Once we release right click, we should unlock the cursor from the window.
    auto isRightClickReleased = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE;
    if (isRightClickReleased)
        _isMouseLocked = false;

    glfwSetInputMode(window, GLFW_CURSOR, _isMouseLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

    if (!_isMouseLocked)
        return;
}
