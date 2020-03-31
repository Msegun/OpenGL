#version 330

// Predefiniowane dane wejsciowe
in vec4 inPosition;
// in int gl_VertexID;

// Predefiniowane dane wyjsciowe
// out vec4 gl_Position;


void main()
{


	// finalna pozycja wierzcholka
	// slowo kluczowe
	gl_Position = inPosition;


}
