#version 150

in vec4 inoutPos;
in vec3 inoutColor;
in vec2 inoutUV;

out vec4 outColor;

// Sampler tekstury
uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
    float dist = 1 - sqrt(gl_FragCoord.x * gl_FragCoord.x + gl_FragCoord.y * gl_FragCoord.y);
    vec4 texture0 = texture(tex0, inoutUV);
    vec4 texture1 = texture(tex1, inoutUV);
    // PRZY MAGICZNYM POŁACZENIU TYCH TEKSTUR UTWORZYŁEM TEKSTURE LAWY
    // ZOSTAWIAM BO MNIE SMIESZY : D
    outColor = mix(texture0, texture1, dist);
}
