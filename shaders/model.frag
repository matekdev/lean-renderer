#version 330 core

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPosition;

out vec4 FragColor;

uniform bool HasTexture;
uniform vec3 ModelColor;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform sampler2D texture_diffuse1;

void main()
{
    vec4 outputColor = vec4(1.0);
    if (HasTexture)
        outputColor = texture(texture_diffuse1, TexCoord);

    // ambient light
    float ambientLightingStrength = 0.1;
    vec3 ambientLight = ambientLightingStrength * LightColor;

    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPosition - FragPosition);
    float diffuseImpact = max(dot(norm, lightDirection), 0.0);
    vec3 diffuseLight = diffuseImpact * LightColor;

    FragColor = outputColor * vec4((ambientLight + diffuseLight) * ModelColor, 1.0);
}
