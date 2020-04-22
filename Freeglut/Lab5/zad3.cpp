#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


enum
{
    LIGHT_OFF = 0,
    LIGHT_GOURAUD,
    LIGHT_PHONG,
    LIGHT_NORMAL,
    LIGHT_NUMBER,
    LIGHT_DISTANCE
};

int MODE = LIGHT_DISTANCE;

#include "obj_loader.hpp"
#include "shader_stuff.h"

// ---------------------------------------
GLuint program[6];
GLuint vBuffer_coord;
GLuint vBuffer_normal;
GLuint vArray;



// ---------------------------------------
glm::mat4x4 Matrix_proj;
glm::mat4x4 Matrix_mv;
glm::mat4x4 Matrix_proj_mv;


// ---------------------------------------
// Na potrzeby pliku OBJ
std::vector<glm::vec3> OBJ_vertices;
std::vector<glm::vec2> OBJ_uvs;
std::vector<glm::vec3> OBJ_normals;

GLfloat _scene_translate_x;
GLfloat _scene_translate_y;
GLfloat _scene_translate_z = -5;
GLfloat _scene_rotate_x;
GLfloat _scene_rotate_y;
GLint prevX = 0.0;
GLint prevY = 0.0;


// ---------------------------------------
// NOWE : OSWIETLENIE - parametry
// ---------------------------------------

glm::vec3 Light_Ambient = glm::vec3(0.2, 0.2, 0.2);
glm::vec3 Light_Diffuse = glm::vec3(1.0, 1.0, 1.0);
glm::vec3 Light_Position = glm::vec3(0.0, 1.0, -3.0);


// ---------------------------------------
void DisplayScene()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glBindVertexArray( vArray );
    glUseProgram( program[MODE] );

    // ------------------------------------------------------
    // NOWE: OSWIETLENIE - przekazanie parametrow do shaderow
    // ------------------------------------------------------
    glUniform3fv( glGetUniformLocation( program[MODE], "Light_Ambient" ), 1, &Light_Ambient[0] );
    glUniform3fv( glGetUniformLocation( program[MODE], "Light_Diffuse" ), 1, &Light_Diffuse[0] );
    glUniform3fv( glGetUniformLocation( program[MODE], "Light_Position" ), 1, &Light_Position[0] );


    // Geometria sceny
    Matrix_mv = glm::mat4x4( 1.0 );
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( _scene_translate_x, _scene_translate_y, _scene_translate_z ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    Matrix_proj_mv = Matrix_proj * Matrix_mv;
    glUniformMatrix4fv( glGetUniformLocation( program[MODE], "Matrix_proj_mv" ), 1, GL_FALSE, glm::value_ptr(Matrix_proj_mv) );


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays( GL_TRIANGLES, 0, OBJ_vertices.size() );

    glUseProgram( 0 );
    glBindVertexArray( 0 );

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

    if (!loadOBJ("objects/scene.obj", OBJ_vertices, OBJ_uvs, OBJ_normals))
    {
        printf("Not loaded!\n");
        exit(1);
    }

    _scene_translate_z = -20;

    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

    // 1. Programowanie potoku
    program[LIGHT_OFF] = glCreateProgram();
    glAttachShader( program[LIGHT_OFF], LoadShader(GL_VERTEX_SHADER, "shaders/off_vertex2.glsl"));
    glAttachShader( program[LIGHT_OFF], LoadShader(GL_FRAGMENT_SHADER, "shaders/off_fragment2.glsl"));
    LinkAndValidateProgram( program[LIGHT_OFF] );


    program[LIGHT_GOURAUD] = glCreateProgram();
    glAttachShader( program[LIGHT_GOURAUD], LoadShader(GL_VERTEX_SHADER, "shaders/gouraud_vertex2.glsl"));
    glAttachShader( program[LIGHT_GOURAUD], LoadShader(GL_FRAGMENT_SHADER, "shaders/gouraud_fragment2.glsl"));
    LinkAndValidateProgram( program[LIGHT_GOURAUD] );

    program[LIGHT_PHONG] = glCreateProgram();
    glAttachShader( program[LIGHT_PHONG], LoadShader(GL_VERTEX_SHADER, "shaders/phong_vertex2.glsl"));
    glAttachShader( program[LIGHT_PHONG], LoadShader(GL_FRAGMENT_SHADER, "shaders/phong_fragment2.glsl"));
    LinkAndValidateProgram( program[LIGHT_PHONG] );

    program[LIGHT_NORMAL] = glCreateProgram();
    glAttachShader( program[LIGHT_NORMAL], LoadShader(GL_VERTEX_SHADER, "shaders/normal_vertex2.glsl"));
    glAttachShader( program[LIGHT_NORMAL], LoadShader(GL_FRAGMENT_SHADER, "shaders/normal_fragment2.glsl"));
    LinkAndValidateProgram( program[LIGHT_NORMAL] );

    program[LIGHT_DISTANCE] = glCreateProgram();
    glAttachShader( program[LIGHT_DISTANCE], LoadShader(GL_VERTEX_SHADER, "shaders/ld_vertex3.glsl"));
    glAttachShader( program[LIGHT_DISTANCE], LoadShader(GL_FRAGMENT_SHADER, "shaders/ld_fragment3.glsl"));
    LinkAndValidateProgram( program[LIGHT_DISTANCE] );

    // 2. Vertex arrays
    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // Wspolrzedne wierzchokow
    glGenBuffers( 1, &vBuffer_coord );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_coord );
    glBufferData( GL_ARRAY_BUFFER, OBJ_vertices.size() * sizeof(glm::vec3), &OBJ_vertices[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    // Wektory normalne
    glGenBuffers( 1, &vBuffer_normal );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_normal );
    glBufferData( GL_ARRAY_BUFFER, OBJ_normals.size() * sizeof(glm::vec3), &OBJ_normals[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 1 );

    glEnable( GL_DEPTH_TEST );

}

void Mouse(int button, int state, int x, int y){
    if(button == 3){
        _scene_translate_z += 0.2;
    }
    if(button == 4){
        _scene_translate_z -= 0.2;
    }
    glutPostRedisplay();
}

void Motion(int x, int y){
    _scene_rotate_x = (x-prevX) * 0.005;
    _scene_rotate_y = (y-prevY) * 0.005;
    glutPostRedisplay();
}

void Keyboard(unsigned char c, int x, int y){
    int nr = c - '0';
    MODE = nr % 6;
    glutPostRedisplay();
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
    glutMouseFunc( Mouse );
    glutKeyboardFunc( Keyboard );
    glutMotionFunc( Motion );

    glutMainLoop();

    // Cleaning();
    glDeleteProgram( program[0] );
    glDeleteProgram( program[1] );
    glDeleteProgram( program[2] );
    glDeleteBuffers( 1, &vBuffer_coord );
    glDeleteBuffers( 1, &vBuffer_normal );
    glDeleteVertexArrays( 1, &vArray );

    return 0;
}