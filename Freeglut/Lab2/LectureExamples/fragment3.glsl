#version 330

// Dane przekazane z poprzednich etapow
in vec4 mojKolor;
out vec4 outColor;

// Zmienna pobrana z aplikacji
uniform float mojP;


void main()
{

	vec4 kolor = mojKolor;
	kolor = kolor * mojP;
    outColor = kolor;
}
