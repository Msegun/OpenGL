#version 330

// Predefiniowane dane wejsciowe
in vec4 inPosition;

void main()
{
    float x = inPosition.x;
    float y = inPosition.y;
    float z = inPosition.z;

    // Y is set to 0 because we want to draw something flat
    vec4 pos = vec4(x, -z, 0, 1); // ????? CO KURWA ???

    gl_Position = pos;
}
