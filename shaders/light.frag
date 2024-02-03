#version 330 core

out vec4 FragColor;

uniform vec3 ModelColor;

void main()
{
    FragColor = vec4(ModelColor, 1.0);
}
