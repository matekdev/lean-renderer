#version 330 core

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess; // Impacts the scattering/radius of specular
};

struct Light {
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Attenuation;
};

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPosition;

out vec4 FragColor;

uniform vec3 CameraPosition;
uniform vec3 LightPosition;
uniform bool HasTexture;
uniform vec3 ModelColor;
uniform Light LightSettings;
uniform Material MaterialSettings;
uniform sampler2D texture_diffuse1;

void main()
{
    vec4 outputColor = vec4(1.0);
    if (HasTexture)
        outputColor = texture(texture_diffuse1, TexCoord);

    // ambient light
    vec3 ambientLight = LightSettings.Ambient * MaterialSettings.Ambient;

    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPosition - FragPosition);
    float diffuseImpact = max(dot(norm, lightDirection), 0.0);
    vec3 diffuseLight = LightSettings.Diffuse * (diffuseImpact * MaterialSettings.Diffuse);

    // specular light
    vec3 viewDirection = normalize(CameraPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), MaterialSettings.Shininess);
    vec3 specularLight = LightSettings.Specular * (specularStrength * MaterialSettings.Specular);

    // attenuation
    float distance = length(LightSettings.Position - FragPosition);
    float attenuation = 1.0 / (distance * LightSettings.Attenuation);

    ambientLight  *= attenuation; 
    diffuseLight  *= attenuation;
    specularLight *= attenuation;   

    vec3 result = ambientLight + diffuseLight + specularLight;
    FragColor = outputColor * vec4(result, 1.0);
}
