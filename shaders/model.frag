#version 330 core

in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform bool HasTexture;
uniform vec3 ModelColor;
uniform vec3 LightColor;
uniform sampler2D texture_diffuse1;

void main()
{
    vec4 outputColor = vec4(1.0);
    if (HasTexture)
        outputColor = texture(texture_diffuse1, TexCoord);

    FragColor = outputColor * vec4(LightColor * ModelColor, 1.0);
}
