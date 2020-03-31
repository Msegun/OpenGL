#version 330

#define POSITION 0
#define COLOR 1

// Wskazanie lokalizacji odpowiednich atrybutow wierzcholkow
// Indeksy atrybutow musza byc te same co w aplikacji
// glVertexAttribPointer( POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL );

layout( location = POSITION ) in vec4 inPosition;
layout( location = COLOR ) in vec4 inColor;


// Do kolejnego etapu renderingu wysylamy zmienna inoutColor
out vec4 mojKolor;


void main()
{

	// finalna pozycja wierzcholka
	vec4 pos = inPosition;
    pos += 0.5f;
    gl_Position = pos;
	// ustawiamy wartosc zmiennej ktora przejdzie do
	// fragment shadera, tam aby ja odebrac nalezy uzyc
	// tej samej nazwy zmiennej

	mojKolor = inColor;

}
