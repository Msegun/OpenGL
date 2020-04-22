#version 330

#define POSITION 0
#define COLOR 1

// Wskazanie lokalizacji odpowiednich atrybutow wierzcholkow
// Indeksy atrybutow musza byc te same co w aplikacji
layout( location = POSITION ) in vec4 inPosition;
layout( location = COLOR ) in vec4 inColor;

out vec4 customColor;

void main()
{
    gl_Position = inPosition;
    customColor = inColor;
}