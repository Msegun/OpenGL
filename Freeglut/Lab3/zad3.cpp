#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "shader_stuff.h"
#include "teapot.h"

// ---------------------------------------
// Identyfikatory obiektow

GLuint program;
GLuint vBuffer_coord;
GLuint vBuffer_color;
GLuint elementbuffer;
GLuint vArray;
std::vector<unsigned int> indices;

float z_camera = -10;

// ---------------------------------------
// Macierze przeksztalcen i rzutowania

glm::mat4x4 Matrix_proj;	// projection matrix
glm::mat4x4 Matrix_mv;		// modelview matrix
glm::mat4x4 Matrix_proj_mv;	// projection*modelview matrix


// Zmienna kontrolujaca obrot szescianu
GLfloat angleX = 0.0;
GLfloat angleY = 0.0;
GLfloat x_placement = 0.0;
GLfloat y_placement = 0.0;
GLint prevX = 0.0;
GLint prevY = 0.0;

// ---------------------------------------
void DisplayScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Matrix_mv = glm::mat4x4( 1.0 );

    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( x_placement, y_placement, z_camera ) );
    Matrix_mv = glm::rotate( Matrix_mv, angleX, glm::vec3( 1.0, 0.0, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, angleY, glm::vec3( 0.0, 1.0, 0.0f ) );

    Matrix_proj_mv = Matrix_proj * Matrix_mv;

    glUniformMatrix4fv( glGetUniformLocation( program, "Matrix_proj_mv" ), 1, GL_FALSE, glm::value_ptr(Matrix_proj_mv) );

    glDrawElements(GL_TRIANGLES, TEAPOT_INDICES_COUNT*3, GL_UNSIGNED_INT, 0);
    glutSwapBuffers();
}


// ---------------------------------------
void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    //Matrix_proj = glm::frustum( -1.0f, 1.0f, (-1.0f*height)/width, 1.0f*height/width, 1.0f, 4.f );
    Matrix_proj = glm::perspective(glm::radians(80.0f), (float)width/(float)height, 0.1f, 100.f );
}

void Mouse(int button, int state, int x, int y){
    if(button == 3){
        z_camera += 0.2;
    }
    if(button == 4){
        z_camera -= 0.2;
    }
    glutPostRedisplay();
}

void Motion(int x, int y){
    angleY = (x-prevX) * 0.005;
    angleX = (y-prevY) * 0.005;
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y){
    if(key == 'w'){
        y_placement += 0.2;
    }
    if(key == 's'){
        y_placement -= 0.2;
    }
    if(key == 'a'){
        x_placement -= 0.2;
    }
    if(key == 'd'){
        x_placement += 0.2;
    }

    glutPostRedisplay();
}

void Initialize()
{

    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );

    program = glCreateProgram();

    glAttachShader( program, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
    glAttachShader( program, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

    LinkAndValidateProgram( program );

    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // Wspolrzedne wierzchokow
    glGenBuffers( 1, &vBuffer_coord );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_coord );
    glBufferData( GL_ARRAY_BUFFER, sizeof( teapotPosition ), &teapotPosition[0], GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    // INDEKSOWANIE // VBO INDEXING : P
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( teapotIndices ), teapotIndices, GL_STATIC_DRAW);

    // -- KOLORY
    glGenBuffers( 1, &vBuffer_color );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_color  );
    glBufferData( GL_ARRAY_BUFFER, sizeof( teapotPosition ), teapotPosition, GL_STATIC_DRAW );

    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 1 );

    glBindVertexArray( 0 );

    glEnable( GL_DEPTH_TEST );

    glBindVertexArray( vArray );
    glUseProgram( program );

}

// ---------------------------------------------------
int main( int argc, char *argv[] )
{
    // GLUT
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutInitWindowSize( 500, 500 );
    glutCreateWindow( "Cube" );

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
    glutDisplayFunc( DisplayScene );
    glutReshapeFunc( Reshape );
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();

    // Cleaning();
    glDeleteProgram( program );
    glDeleteBuffers( 1, &vBuffer_coord );
    glDeleteBuffers( 1, &vBuffer_color );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}