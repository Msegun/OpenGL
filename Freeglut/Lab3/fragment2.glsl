#version 150

in vec4 inoutPos;
in vec3 inoutColor;
in vec2 inoutUV;

out vec4 outColor;

// Sampler tekstury
uniform sampler2D tex0;

void main()
{
    outColor = texture( tex0, inoutUV );
}
