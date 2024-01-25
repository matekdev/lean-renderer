#include "camera.hpp"

#include "game.hpp"
#include "log.hpp"

#include <GLFW/glfw3.h>

Camera::Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
    return _viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return _projectionMatrix;
}

void Camera::Update(float width, float height, Shader &shader)
{
    _velocity *= VELOCITY_DECAY;
    _position += _velocity * Game::DeltaTime;

    _viewMatrix = glm::lookAt(_position, _position + _orientation, UP);
    _projectionMatrix = glm::perspective(glm::radians(90.0f), width / height, 0.1f, 100.0f);

    shader.SetMat4(_projectionMatrix * _viewMatrix, "cameraMatrix");
}

void Camera::Input(float width, float height, GLFWwindow *window, bool isWindowHovered)
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

    MouseMovement(width, height, window);
    KeyboardMovement(window);
}

void Camera::MouseMovement(float width, float height, GLFWwindow *window)
{
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glfwSetCursorPos(window, (width / 2), (height / 2));

    float rotationX = SENSITIVITY * (float)(mouseY - (height / 2)) / height;
    float rotationY = SENSITIVITY * (float)(mouseX - (width / 2)) / width;

    glm::vec3 newOrientation = glm::rotate(_orientation, glm::radians(-rotationX), glm::normalize(glm::cross(_orientation, UP)));

    if (abs(glm::angle(newOrientation, UP) - glm::radians(90.0f)) <= glm::radians(85.0f))
        _orientation = newOrientation;

    _orientation = glm::rotate(_orientation, glm::radians(-rotationY), UP);
}

void Camera::KeyboardMovement(GLFWwindow *window)
{
    auto movementSpeed = 0.2f;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movementSpeed *= 4;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movementSpeed /= 4;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _velocity += movementSpeed * _orientation;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _velocity += movementSpeed * -glm::normalize(glm::cross(_orientation, UP));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _velocity += movementSpeed * -_orientation;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _velocity += movementSpeed * glm::normalize(glm::cross(_orientation, UP));
}
