#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint program;
GLuint vBuffer_coord;
GLuint vBuffer_color;
GLuint vArray;

// ---------------------------------------
// Macierze przeksztalcen i rzutowania

glm::mat4x4 Matrix_proj;	// projection matrix
glm::mat4x4 Matrix_mv;		// modelview matrix
glm::mat4x4 Matrix_proj_mv;	// projection*modelview matrix


// Zmienna kontrolujaca obrot szescianu
GLfloat obrot = 0.0;

// ---------------------------------------
// Wspolrzedne wierzchokow
GLfloat triangles_coord[6*6*3] =
        {
                // Top face
                0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, -0.5f,

                // Bottom face
                0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, 0.5f,

                // Front face
                0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,

                // Back face
                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,

                // Left face
                -0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,

                // Right face
                0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f
        };


// ---------------------------------------
// Kolory wierzcholkow
GLfloat triangles_color[6*6*3] =
        {
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,

                1.0f, 0.5f, 0.0f,
                1.0f, 0.5f, 0.0f,
                1.0f, 0.5f, 0.0f,
                1.0f, 0.5f, 0.0f,
                1.0f, 0.5f, 0.0f,
                1.0f, 0.5f, 0.0f,

                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,

                1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f,

                0.5f, 0.0f, 0.5f,
                0.5f, 0.0f, 0.5f,
                0.5f, 0.0f, 0.5f,
                0.5f, 0.0f, 0.5f,
                0.5f, 0.0f, 0.5f,
                0.5f, 0.0f, 0.5f
        };


// ---------------------------------------
void DisplayScene()
{
    // Czyszczenie ramki
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // ------------------------------
    // 1. Geometria sceny
    // Ustawiamy macierz jednostkowa
    Matrix_mv = glm::mat4x4( 1.0 );

    // Przesuwamy srodek ukladu o 2 jednostki za ekran (oddalamy)
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( 0.0f, 0.0f, -2.0 ) );

    // Obracamy srodek ukladu
    Matrix_mv = glm::rotate( Matrix_mv, obrot, glm::vec3( 1.0f, 1.0f, 0.0f ) );

    // ------------------------------
    // 2. Obliczenie macierzy rzutowania
    // (wlasciwie mnozenie mogloby sie odbyc w vs, ale...?)

    Matrix_proj_mv = Matrix_proj * Matrix_mv;

    // ------------------------------
    // 3. Przekazanie macierzy do vertex shadera
    glUniformMatrix4fv( glGetUniformLocation( program, "Matrix_proj_mv" ), 1, GL_FALSE, glm::value_ptr(Matrix_proj_mv) );

    // ------------------------------
    // 4. Generowanie obiektow na ekranie
    glDrawArrays( GL_TRIANGLES, 0, 6*6*3 );

    // ------------------------------
    // ZADANIE 1: Wygeneruj kolejny szescian obok/na gorze itp.
    // ZADANIE 2: Spraw aby obracal sie w druga strone bez dodawania zadnej nowej zmiennej

    glutSwapBuffers();
}


// ---------------------------------------
void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    //Matrix_proj = glm::frustum( -1.0f, 1.0f, (-1.0f*height)/width, 1.0f*height/width, 1.0f, 4.f );
    Matrix_proj = glm::perspective(glm::radians(80.0f), (float)width/(float)height, 0.1f, 100.f );
}

// ---------------------------------------------------
void Initialize()
{

    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );

    // 1. Programowanie potoku
    program = glCreateProgram();

    glAttachShader( program, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
    glAttachShader( program, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

    LinkAndValidateProgram( program );


    // 2. Vertex arrays

    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // Wspolrzedne wierzchokow
    glGenBuffers( 1, &vBuffer_coord );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_coord );
    glBufferData( GL_ARRAY_BUFFER, sizeof( triangles_coord ), triangles_coord, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    // Kolor wierzcholkow

    glGenBuffers( 1, &vBuffer_color );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_color  );
    glBufferData( GL_ARRAY_BUFFER, sizeof( triangles_color ), triangles_color, GL_STATIC_DRAW );

    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 1 );

    glBindVertexArray( 0 );

    glEnable( GL_DEPTH_TEST );


    // Wlaczenie VA i programu
    glBindVertexArray( vArray );
    glUseProgram( program );

}


// ---------------------------------------------------
void Animation(int frame)
{
    // Obracanie szescianu
    obrot += 0.01f;
    if (obrot > 2*3.14f) obrot = 0.f;

    glutPostRedisplay();
    glutTimerFunc(10, Animation, 0);
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

    glutTimerFunc(100, Animation, 0);

    glutMainLoop();

    // Cleaning();
    glDeleteProgram( program );
    glDeleteBuffers( 1, &vBuffer_coord );
    glDeleteBuffers( 1, &vBuffer_color );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}