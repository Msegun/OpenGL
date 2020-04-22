#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "obj_loader.hpp"
#include "texture_loader.hpp"
#include "shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint program;
GLuint vBuffer_pos;
GLuint vBuffer_uv;
GLuint vBuffer_normal;
GLuint vArray;



// ---------------------------------------
// Macierze przeksztalcen i rzutowania

glm::mat4x4 Matrix_proj;	// projection matrix
glm::mat4x4 Matrix_mv;		// modelview matrix
glm::mat4x4 Matrix_proj_mv;	// projection*modelview matrix


std::vector<glm::vec3> OBJ_vertices;
std::vector<glm::vec2> OBJ_uvs;
std::vector<glm::vec3> OBJ_normals;


// ---------------------------------------
void DisplayScene()
{

    // 0. Czyszczenie ramki
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // 1. Geometria sceny
    Matrix_mv = glm::mat4x4( 1.0 );
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( 0, 0, -5 ) );
    Matrix_mv = glm::rotate( Matrix_mv, 0.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, 0.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    Matrix_proj_mv = Matrix_proj * Matrix_mv;
    glUniformMatrix4fv( glGetUniformLocation( program, "Matrix_proj_mv" ), 1, GL_FALSE, glm::value_ptr(Matrix_proj_mv) );


    // 2. Generowanie obiektow na ekranie
    glDrawArrays( GL_TRIANGLES, 0, OBJ_vertices.size() );



    glutSwapBuffers();
}


// ---------------------------------------
void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    Matrix_proj = glm::perspectiveFov(glm::radians(60.0f), (float)width, (float)height, 0.1f, 100.f );
}

// ---------------------------------------------------
void Initialize()
{

    // Ladowanie pliku OBJ
    if (!loadOBJ("cube.obj", OBJ_vertices, OBJ_uvs, OBJ_normals))
    {
        printf("Not loaded!\n");
        exit(1);
    }



    // Odsuwanie widoku (na potrzeby przykladu)
//    _scene_translate_z = -5;
    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );


    // Programowanie potoku
    program = glCreateProgram();

    glAttachShader( program, LoadShader(GL_VERTEX_SHADER, "vertex2.glsl"));
    glAttachShader( program, LoadShader(GL_FRAGMENT_SHADER, "fragment2.glsl"));

    LinkAndValidateProgram( program );



    // Vertex arrays

    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // Wspolrzedne wierzchokow
    glGenBuffers( 1, &vBuffer_pos );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_pos );
    glBufferData( GL_ARRAY_BUFFER, OBJ_vertices.size() * sizeof(glm::vec3), &OBJ_vertices[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    // Wspolrzedne textury UV
    glGenBuffers( 1, &vBuffer_uv );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_uv );
    glBufferData( GL_ARRAY_BUFFER, OBJ_uvs.size() * sizeof(glm::vec2), &OBJ_uvs[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 1 );

    // Wektory normalne
    glGenBuffers( 1, &vBuffer_normal );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_normal );
    glBufferData( GL_ARRAY_BUFFER, OBJ_normals.size() * sizeof(glm::vec3), &OBJ_normals[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 2 );




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
    glutCreateWindow( "OpenGL" );

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
//    glutMouseFunc( MouseButton );
//    glutMotionFunc( MouseMotion );
//    glutMouseWheelFunc( MouseWheel );
//    glutKeyboardFunc( Keyboard );
//    glutSpecialFunc( SpecialKeys );

    glutMainLoop();

    // Cleaning();
    glDeleteProgram( program );
    glDeleteBuffers( 1, &vBuffer_pos );
    glDeleteBuffers( 1, &vBuffer_uv );
    glDeleteBuffers( 1, &vBuffer_normal );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}