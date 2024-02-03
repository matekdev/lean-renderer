#version 330 core

out vec4 FragColor;

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform Material LightSettings;

void main()
{
    FragColor = vec4(LightSettings.Ambient * LightSettings.Diffuse, 1.0);
}
