#version 330


// Predefiniowane dane wejsciowe i wyjsciowe
in  vec4 gl_FragCoord;

in vec4 customColor;
out vec4 outColor;

void main()
{
    outColor = customColor;
}
