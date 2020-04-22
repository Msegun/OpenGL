#version 150 core

in vec4 ourPosition;
in vec3 ourNormal;

out vec4 outColor;


// Parametry oswietlenia
uniform vec3 Light_Ambient;
uniform vec3 Light_Diffuse;
uniform vec3 Light_Position;


void main()
{

    vec3 objectColor = vec3(0.2, 0.8, 0.2);
    vec3 shadeColor = vec3(0.2, 0.2, 0.2);
    vec3 lightDirection = normalize(Light_Position - vec3(ourPosition));

    float lightCoeff = max(dot(ourNormal, lightDirection), 0.0);

    // obliczenie skladowej diffuse
    vec3 resultDiffuse = lightCoeff * Light_Diffuse;
    // SERIO ŁADNIE TO WYGLADA
    float distance = length(Light_Position - vec3(ourPosition));
    float attenuation = clamp(2.f/distance, 0.0, 1.0);


    // Zastosowanie oswietlenia do fragmentu
    vec3 result = (Light_Ambient + resultDiffuse) * objectColor * attenuation;

    outColor = vec4(result, 1.0) + (1-attenuation)*vec4(shadeColor, 1.0);
}
