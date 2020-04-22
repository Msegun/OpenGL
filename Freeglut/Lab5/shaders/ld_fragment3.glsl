#version 150 core

in vec4 ourPosition;
in vec3 ourNormal;

out vec4 outColor;

#define MAX_LIGHTS 3
vec3 Light_Positions[MAX_LIGHTS];
// Parametry oswietlenia
uniform vec3 Light_Ambient;
uniform vec3 Light_Diffuse;


void main()
{
    Light_Positions[0] = vec3(0.0, 1.0, -2.0);
    Light_Positions[1] = vec3(10.0, 1.0, -2.0);
    Light_Positions[2] = vec3(-10.0, 1.0, 10.0);

    vec3 objectColor = vec3(0.2, 0.8, 0.2);
    vec3 shadeColor = vec3(0.2, 0.2, 0.2);

    vec3 pointLights = vec3(0.0);
    float att;
    for(int i = 0 ; i < MAX_LIGHTS; i++){
        vec3 lightDirection = normalize(Light_Positions[i] - vec3(ourPosition));
        float lightCoeff = max(dot(ourNormal, lightDirection), 0.0);
        vec3 resultDiffuse = lightCoeff * Light_Diffuse;
        float distance = length(Light_Positions[i] - vec3(ourPosition));
        float attenuation = clamp(2.f/distance, 0.0, 1.0);
        att += attenuation;
        pointLights += resultDiffuse*attenuation;
    }
    // Zastosowanie oswietlenia do fragmentu
    vec3 result = (Light_Ambient + pointLights) * objectColor;

    outColor = vec4(result, 1.0);
}
