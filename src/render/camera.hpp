#pragma once

#include "render/shader.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera
{
public:
    Camera();

    void UpdateMatrix(int width, int height, Shader &shader);

private:
    const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 ORIENTATION = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 2.0f);
};