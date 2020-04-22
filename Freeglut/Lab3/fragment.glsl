#version 150

//in vec4 inoutColor;
//in vec4 inoutCoord;

in VS_OUT
{
    vec4 coord;
    flat vec4 color;
} fs_in;

out vec4 outColor;

void main()
{
    vec4 red = vec4(1.0, 1.0, 0.0, 0.0);
    float alpha = gl_FragCoord.y/500;
    outColor = mix(red, fs_in.color, alpha);
}
