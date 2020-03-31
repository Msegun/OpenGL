#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Identyfikatory obiektow
GLuint program;	// programu
GLuint vBuffer;	// bufora z danymi tablicy wierzcholkow
GLuint vArray;	// tablic wierzcholkow

// Wspolrzedne wierzchokow
GLfloat triangles[1*3*2] =
{
    -1.f, -1.f,
    1.f, -1.f,
    0.f,  1.f,
};
#define NUMBER 20
GLfloat triangles2[NUMBER* 3 * 2];

void triangle_matrix(){
    for (int i=0; i < NUMBER*3*2; ++i){
        triangles2[i] = (rand()%100 / 50-1 );
    }
}

// To fill definition
GLuint CreateVertexShader( void )
{
    GLuint shader = glCreateShader( GL_VERTEX_SHADER );

    const GLchar * code =
            "#version 330 \n			"
            "layout( location = 0 ) in vec4 inPosition;	"
            "void main() 				"
            "{ 							"
            "	gl_Position = inPosition; "
            "}							";

    glShaderSource( shader, 1, &code, NULL );
    glCompileShader( shader );

    GLint status;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if( status != GL_TRUE )
    {
        printf("Blad!\n");
        exit(1);
    }
    glAttachShader( program, shader );
}

void CreateFragmentShader( void )
{
    GLuint shader = glCreateShader( GL_FRAGMENT_SHADER );

    const GLchar *code =
            "#version 150 \n			"
            "out vec4 outColor;			"
            "void main()				"
            "{							"
            "	outColor = vec4( 0.f, 1.f, 0.f, 1.f ); "
            "}";


    glShaderSource( shader, 1, &code, NULL );
    glCompileShader( shader );

    GLint status;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if( status != GL_TRUE )
    {
        printf("Blad!\n");
        exit(1);
    }
    glAttachShader( program, shader );
}

void Initialize()
{

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    // 1. Program
    // Stworzenie programu i shaderow
    program = glCreateProgram();
    CreateVertexShader();
    CreateFragmentShader();
    // Walidacja programu
    glLinkProgram( program );
    glValidateProgram( program );

    // 2. Dane
    // Stworzenie identyfikatora obiektu oraz obiektu tablic wierzcholkow
    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );
    // Generowanie identyfikatora obiektu oraz obiektu bufora
    glGenBuffers( 1, &vBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer );
    // Zaladowanie danych do obiektu bufora wierzcholkow
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*NUMBER*6, triangles2, GL_STATIC_DRAW );
    // Ustawienie indeksu atrybutu wierzcholka o nazwie "inPosition" Gdyby 3d to 3 atrybut 3 zamiast 2
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );
    // wylaczenie obiektu tablic wierzcholkow
    glBindVertexArray( 0 );
}

void DisplayScene()
{
    // 1. czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );
    // 2. wlaczenie obiektu tablic wierzcholkow
    glBindVertexArray( vArray );
    // 3. uruchomienie programu
    glUseProgram( program );

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 4. rysowanie danych z tablic wierzcholkow
    glDrawArrays( GL_TRIANGLES, 0, NUMBER*3 );
    // 5. wylaczenie shadera
    glUseProgram( 0 );
    // 6. wylaczenie obiektu tablic wierzcholkow
    glBindVertexArray( 0 );

    glutSwapBuffers();
}

void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
}

int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "Hello World!" );

    glutDisplayFunc( DisplayScene );
    glutReshapeFunc( Reshape );

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if( GLEW_OK != err )
    {
        printf("GLEW Error\n");
        exit(1);
    }

    // OpenGL
    if( !GLEW_VERSION_3_2 )
    {
        printf("Brak OpenGL 3.2!\n");
        exit(1);
    }
    if( !GLEW_VERSION_3_3 )
    {
        printf("Brak OpenGL 3.3!\n");
        exit(1);
    }

    Initialize();
    glutMainLoop();

    // Cleaning
    glDeleteProgram( program );
    glDeleteBuffers( 1, &vBuffer );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}