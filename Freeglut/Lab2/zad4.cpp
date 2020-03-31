#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "house.h"
#include "shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint program;
GLuint vBuffer_coord;
GLuint vArray;


// ---------------------------------------
void DisplayScene()
{

    glClear( GL_COLOR_BUFFER_BIT );

    // Wlaczenie VA i programu
    glBindVertexArray( vArray );
    glUseProgram( program );

    // Generowanie obiektow na ekranie
    glDrawArrays( GL_TRIANGLES, 0, 7*3 );


    // Wylaczanie
    glUseProgram( 0 );
    glBindVertexArray( 0 );

    glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    // 1. Program i shadery
    program = glCreateProgram();

    glAttachShader( program, LoadShader(GL_VERTEX_SHADER, "zad4_vertex.glsl"));
    glAttachShader( program, LoadShader(GL_FRAGMENT_SHADER, "zad4_fragment.glsl"));

    LinkAndValidateProgram( program );


    // 2. Vertex arrays
    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // Wspolrzedne wierzcholkow
    glGenBuffers( 1, &vBuffer_coord );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_coord );
    glBufferData( GL_ARRAY_BUFFER, sizeof( house_mesh_of_vertices ), house_mesh_of_vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( 0 );

}

// ---------------------------------------
void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
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
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}