#version 330


// Predefiniowane dane wejsciowe i wyjsciowe
in  vec4 gl_FragCoord;

in vec4 customColor;
out vec4 outColor;

void main()
{
    // For each freagment grayscaled value (dot product) is calculated.
    // It is based on fragment color and aditional vector
    // Might've as well just painted it grey or black
    float gray = dot(customColor.rgba, vec4(0.25, 0.25, 0.25, 0));
    outColor = vec4(gray);
}
