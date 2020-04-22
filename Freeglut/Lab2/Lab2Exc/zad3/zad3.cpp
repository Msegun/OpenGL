#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "shader_stuff.h"


GLuint program[2];
GLuint vBuffer_coord;
GLuint vBuffer_color;
GLuint vArray;
int mode = 0;

GLfloat triangles_coord[3*2] =
        {
                -1.0f, -1.0,
                1.0f, -1.0f,
                0.0f,  1.0f
        };

GLfloat triangles_color[3*3] =
        {
                1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                1.0, 0.0, 1.0
        };


void DisplayScene()
{

    glClear( GL_COLOR_BUFFER_BIT );
    glBindVertexArray( vArray );
    glUseProgram( program[mode] );

//     glUniform1f(glGetUniformLocation( program, "alpha" ), alpha );

    glDrawArrays( GL_TRIANGLES, 0, 1*3 );

    glUseProgram( 0 );
    glBindVertexArray( 0 );
    glutSwapBuffers();
}

// ---------------------------------------------------
void Initialize()
{

    glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
    // 1. Program i shadery
    program[0] = glCreateProgram();

    glAttachShader( program[0], LoadShader(GL_VERTEX_SHADER, "zad3_vertex.glsl"));
    glAttachShader( program[0], LoadShader(GL_FRAGMENT_SHADER, "zad3_fragment.glsl"));

    LinkAndValidateProgram( program[0] );

    program[1] = glCreateProgram();

    glAttachShader( program[1], LoadShader(GL_VERTEX_SHADER, "zad3_vertex_g.glsl"));
    glAttachShader( program[1], LoadShader(GL_FRAGMENT_SHADER, "zad3_fragment_g.glsl"));

    LinkAndValidateProgram( program[1] );

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

void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
}

void Keyboard(unsigned char ch, int x, int y){
    // Since we assume only mode 1 and 0 we can use negation : P
    if(ch == ' '){
        mode = !mode;
    }
    glutPostRedisplay();
}

int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "OpenGL!" );
    glutDisplayFunc( DisplayScene );
    glutReshapeFunc( Reshape );
    glutKeyboardFunc( Keyboard );

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
    glDeleteProgram( program[0] );
    glDeleteProgram( program[1] );
    glDeleteBuffers( 1, &vBuffer_coord );
    glDeleteBuffers( 1, &vBuffer_color );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}
