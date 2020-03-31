#version 330

#define POSITION 0
#define COLOR 1

layout( location = POSITION ) in vec4 inPosition;
layout( location = COLOR ) in vec4 inColor;

out vec4 mojKolor;

void main()
{
    vec4 pos = inPosition;
    gl_Position = pos;

    mojKolor = inColor;
}