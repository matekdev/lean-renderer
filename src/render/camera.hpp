#pragma once

#include "render/shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

struct GLFWwindow;

class Camera
{
public:
    Camera();

    void Update(int width, int height, Shader &shader);
    void Input(GLFWwindow *window, bool isWindowHovered);

private:
    const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 2.0f);

    bool _isMouseLocked = false;
};