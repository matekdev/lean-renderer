#version 330 core

in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoord) * vec4(color, 1.0);
} 
