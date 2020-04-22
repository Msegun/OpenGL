#version 330

// Dane przekazane z poprzednich etapow
in vec4 mojKolor;
out vec4 outColor;

// Zmienna pobrana z aplikacji
uniform float alpha;


void main()
{
    //Każdy sposób działą : P
    // 1. Bezpośrednie odniesienie do kolorów i dodanie alphy
    if (gl_PrimitiveID % 2 == 0)
        outColor = vec4(mojKolor.r, mojKolor.g, mojKolor.b, alpha);
    if (gl_PrimitiveID % 2 == 1)
        outColor = vec4(mojKolor.r, mojKolor.g, mojKolor.b, 1-alpha);
    // 2. Odniesienie do kolorów jak do wartości w strukturach : P
    // outColor = vec4(mojKolor[0], mojKolor[1], mojKolor[2], alpha);
    //
    // 3.Gdyby mojkolor  był typu vec3 to mozna użyć go do "zainstancjonowania" vec4
    // vec3 kolor = vec3(mojKolor[0], mojKolor[1], mojKolor[2]);
    // outColor = vec4(kolor, alpha);

}
