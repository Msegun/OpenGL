#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


#include "GLProgram.hpp"

GLProgram glprog[4];

glm::mat4x4 Matrix_proj;
glm::mat4x4 Matrix_mv;
glm::mat4x4 Matrix_proj_mv;

GLfloat _scene_translate_x;
GLfloat _scene_translate_y;
GLfloat _scene_translate_z = -5;
GLfloat _scene_rotate_x;
GLfloat _scene_rotate_y;
GLint prevX = 0.0;
GLint prevY = 0.0;


// ---------------------------------------
void DisplayScene()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Geometria sceny
    Matrix_mv = glm::mat4x4( 1.0 );
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( _scene_translate_x-3, _scene_translate_y-1, _scene_translate_z ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    Matrix_proj_mv = Matrix_proj * Matrix_mv;
    glprog[0].draw(Matrix_proj_mv);

    Matrix_mv = glm::mat4x4( 1.0 );
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( _scene_translate_x, _scene_translate_y-0.7, _scene_translate_z ) );
    Matrix_mv = glm::scale(Matrix_mv, glm::vec3(0.5f,0.5f,0.5f));
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    Matrix_proj_mv = Matrix_proj * Matrix_mv;
    glprog[1].draw(Matrix_proj_mv);

    Matrix_mv = glm::mat4x4( 1.0 );
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( _scene_translate_x+3, _scene_translate_y-1, _scene_translate_z ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    Matrix_proj_mv = Matrix_proj * Matrix_mv;
    glprog[2].draw(Matrix_proj_mv);

    Matrix_mv = glm::mat4x4( 1.0 );
    Matrix_mv = glm::translate( Matrix_mv, glm::vec3( _scene_translate_x, _scene_translate_y-1, _scene_translate_z ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    Matrix_mv = glm::rotate( Matrix_mv, _scene_rotate_y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    Matrix_proj_mv = Matrix_proj * Matrix_mv;
    glprog[3].draw(Matrix_proj_mv);

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
    _scene_translate_z = -10;
    glprog[0] = GLProgram();
    glprog[0].loadObject("objects/Table.obj");
    glprog[0].loadBMP("textures/grass.bmp");
    glprog[0].createProgram();
    glprog[0].loadShaders("shaders/ld_vertex4.glsl", "shaders/ld_fragment4.glsl");
    glprog[0].prepareVBO();

    glprog[1] = GLProgram();
    glprog[1].loadObject("objects/seal.obj");
    glprog[1].loadBMP("textures/bubbles.bmp");
    glprog[1].createProgram();
    glprog[1].loadShaders("shaders/ld_vertex4.glsl", "shaders/ld_fragment4.glsl");
    glprog[1].prepareVBO();

    glprog[2] = GLProgram();
    glprog[2].loadObject("objects/der.obj");
    glprog[2].loadBMP("textures/uvtemplate.bmp");
    glprog[2].createProgram();
    glprog[2].loadShaders("shaders/ld_vertex4.glsl", "shaders/ld_fragment4.glsl");
    glprog[2].prepareVBO();

    glprog[3] = GLProgram();
    glprog[3].loadObject("objects/ground.obj");
    glprog[3].loadBMP("textures/grass.bmp");
    glprog[3].createProgram();
    glprog[3].loadShaders("shaders/ld_vertex4.glsl", "shaders/ld_fragment4.glsl");
    glprog[3].prepareVBO();

    glClearColor( 0.2f, 0.2f, 0.8f, 1.0f );

    glEnable( GL_DEPTH_TEST );

}

void Mouse(int button, int state, int x, int y){
    if(button == 3){
        _scene_translate_z += 0.5;
    }
    if(button == 4){
        _scene_translate_z -= 0.5;
    }
    glutPostRedisplay();
}

void Motion(int x, int y){
    _scene_rotate_x = (x-prevX) * 0.005;
    _scene_rotate_y = (y-prevY) * 0.005;
    glutPostRedisplay();
}

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
    glutMotionFunc( Motion );

    glutMainLoop();

    // Cleaning();
//    glDeleteProgram( program );
//    glDeleteBuffers( 1, &vBuffer_coord );
//    glDeleteBuffers( 1, &vBuffer_normal );
//    glDeleteVertexArrays( 1, &vArray );

    return 0;
}