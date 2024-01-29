#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 Model;
uniform mat4 CameraMatrix;

void main()
{
    gl_Position = CameraMatrix * Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
