#version 150

//in vec4 inoutColor;
//in vec4 inoutCoord;

in VS_OUT
{
    vec4 coord;
    vec4 color;
} fs_in;

out vec4 outColor;



void main()
{
    // odleglosc od lokalnego poczatku ukladu wsp;
    // float odl = 1.0 - sqrt(fs_in.coord.x*fs_in.coord.x + fs_in.coord.y*fs_in.coord.y + fs_in.coord.z*fs_in.coord.z);
    // outColor = fs_in.color*odl;
    // dodaj inne efekty np. uzywajac gl_FragCoord lub/i gl_PrimitiveID;

    outColor = fs_in.color;

}