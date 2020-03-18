#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include <cmath>

float eye_x = 2.8;
float eye_y = 2.5;
float eye_z = 2.0;

float teapot_pos_x = 4;
float teapot_pos_y = 0.9;
float teapot_pos_z = 4;

float rot = 0.0;

void draw_teapot_and_pointer(float x, float y, float z, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1, 0, 0);
    glRotatef(rot-90, 0,1,0);
    glutWireTeapot(scale);

    glEnd();

    glPopMatrix();
}

void drawPlane(float x, float y, float z, float scale, float r, float g, float b){
    glBegin(GL_POLYGON); // Top face
    glColor3f(r, g, b);
    glVertex3f(x + scale, y + scale, z - scale);
    glVertex3f(x - scale, y + scale, z - scale);
    glVertex3f(x - scale, y + scale, z + scale);
    glVertex3f(x + scale, y + scale, z + scale);
    glEnd();
}

void init_view(){
    glLoadIdentity();
    gluPerspective(90.0, 8.0/6.0, 0.1, 20);
}

void DrawingFunc(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    init_view();
    gluLookAt(
        eye_x, eye_y, eye_z,
        4,0,4,
        0,1,0
    );

    for(int i = -9; i < 9; i++){
        bool black = i % 2 == 0;
        for(int j =-9; j < 9; j++){
            if (black)
                drawPlane(float(i),0,float(j),0.5, 0, 0, 0);
            else
                drawPlane(float(i),0,float(j),0.5, 1.0, 1.0, 1.0);
            black = !black;
        }
    }
    draw_teapot_and_pointer(teapot_pos_x, teapot_pos_y, teapot_pos_z, 0.5);
    glFlush();
}

void reshape_func (int w, int h)
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 8.0/6.0, 0.1, 20);
}


void keyboard_func(unsigned char key, int x, int y){
    switch( key ) {
        case 'a':
            rot -= 1;
            break;
        case 'd':
            rot += 1;
            break;
        case 'w':
            // Speed
            teapot_pos_x += 0.05 * sin(rot * M_PI / 180);
            teapot_pos_z += 0.05 * cos(rot * M_PI / 180);
            break;
        case 's':
            teapot_pos_x -= 0.05 * sin(rot * M_PI / 180);
            teapot_pos_z -= 0.05 * cos(rot * M_PI / 180);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void special_func( int key, int x, int y )
{
    switch( key ) {
        case GLUT_KEY_LEFT:
            eye_x -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            eye_x += 0.1;
            break;
        case GLUT_KEY_UP:
            eye_y += 0.1;
            break;
        case GLUT_KEY_DOWN:
            eye_y -= 0.1;
            break;
        case GLUT_KEY_CTRL_L:
            eye_z -= 0.1;
            break;
        case GLUT_KEY_ALT_L:
            eye_z += 0.1;
            break;
        default:
            break;
    }
    std::cout << "X:" << eye_x << " | Y:" << eye_y << " | Z:" << eye_z << std::endl;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
    glutInitWindowSize(800, 600);
    if (glutCreateWindow("GLUT Template") < 1)
    {
        printf("glutCreateWindow() failed!\n");
    }
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(DrawingFunc);
    glutReshapeFunc(reshape_func);
    glutSpecialFunc(special_func);
    glutKeyboardFunc(keyboard_func);
    glutIdleFunc(DrawingFunc);
    glutMainLoop();

    return 0;
}