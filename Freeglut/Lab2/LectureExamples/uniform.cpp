#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint program;
GLuint vBuffer_coord;
GLuint vBuffer_color;
GLuint vArray;

float rotate = 0.0;
// ---------------------------------------
// Wspolrzedne wierzchokow
GLfloat triangles_coord[2*3*2] =
        {
                -0.8f, -0.8f,
                0.0f, -0.8f,
                -0.4f,  0.0f,

                0.0f,  0.0f,
                0.8f,  0.0f,
                0.4f,  0.8f
        };

// ---------------------------------------
// Kolory wierzcholkow
GLfloat triangles_color[2*3*3] =
        {
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                0.f, 0.f, 1.f,

                1.f, 1.f, 0.f,
                0.f, 1.f, 1.f,
                1.f, 0.f, 1.f
        };

float alpha = 0.0;

// ---------------------------------------------------
void DisplayScene()
{

    glClear( GL_COLOR_BUFFER_BIT );
    glBindVertexArray( vArray );
    glUseProgram( program );



    // Zmiana wartosci parametru
    alpha = 0.5f;

    // Przekazujemy wartosc zmiennej do programu
    glUniform1f(glGetUniformLocation( program, "mojP" ), alpha );
    glUniform1f( glGetUniformLocation( program, "rotate" ), rotate );



    // Generowanie obiektow na ekranie
    glDrawArrays( GL_TRIANGLES, 0, 2*3 );



    glUseProgram( 0 );
    glBindVertexArray( 0 );
    glutSwapBuffers();
}

// ---------------------------------------------------
void Initialize()
{

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );


    // 1. Program i shadery
    program = glCreateProgram();

    glAttachShader( program, LoadShader(GL_VERTEX_SHADER, "vertex3.glsl"));
    glAttachShader( program, LoadShader(GL_FRAGMENT_SHADER, "fragment3.glsl"));

    LinkAndValidateProgram( program );


    // 2. Vertex arrays

#define POSITION 0
#define COLOR 1

    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // BUFOR: Wspolrzedne wierzcholkow

    glGenBuffers( 1, &vBuffer_coord );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_coord );
    glBufferData( GL_ARRAY_BUFFER, sizeof( triangles_coord ), triangles_coord, GL_STATIC_DRAW );

    glVertexAttribPointer( POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( POSITION );

    // BUFOR: Kolor wierzcholkow

    glGenBuffers( 1, &vBuffer_color );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_color  );
    glBufferData( GL_ARRAY_BUFFER, sizeof( triangles_color ), triangles_color, GL_STATIC_DRAW );

    glVertexAttribPointer( COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( COLOR );

    glBindVertexArray( 0 );

}

// ---------------------------------------------------
void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
}

void Animation(int frame){
    rotate += 0.1f;
    if (rotate > 360)
        rotate = 0.0f;
    glutPostRedisplay();
    glutTimerFunc(100, Animation, 0);
}

// ---------------------------------------------------
int main( int argc, char *argv[] )
{
    // GLUT
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutInitWindowSize( 500, 500 );
    glutCreateWindow( "OpenGL!" );
    glutDisplayFunc( DisplayScene );
    glutReshapeFunc( Reshape );
    glutTimerFunc(1000, Animation, 0);

    // GLEW
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


    Initialize();


    glutMainLoop();

    // Cleaning
    glDeleteProgram( program );
    glDeleteBuffers( 1, &vBuffer_coord );
    glDeleteBuffers( 1, &vBuffer_color );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}
