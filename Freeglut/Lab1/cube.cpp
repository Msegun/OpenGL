#include <iostream>
#include <GL/freeglut.h>
#include <time.h>

clock_t last_t = 0;
float alpha = 1.0;
bool ortho = true;
float eye_x = 1.5;
float eye_y = 0;
float eye_z = 0.8;

void drawCube()
{
    glBegin(GL_LINE_LOOP); // Top face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP); // Bottom face
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP); // Front face
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP); // Back face
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP); // Left face
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP); // Right face
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
}

void init_view(){
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    if (ortho)
        glOrtho(-2, 2, -2, 2, 0.1, 6.0);
    else
        gluPerspective(90.0, 8.0/6.0, 0.1, 20);
}

void DrawingFunc(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    init_view();
    gluLookAt(
            eye_x, eye_y, eye_z,
            0,0,0,
            0,1,0
    );
    drawCube();
    glFlush();
}

void InitFunc(void)
{
    glClearColor( 0.2, 0.2, 0.2, 1 );
    glShadeModel ( GL_SMOOTH );

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glLineWidth(2.0);
    glPointSize(3.0);
}

void ReshapeFunc (int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 8.0/6.0, 0.1, 20);
}

void KeyboardFunc( unsigned char key, int x, int y )
{
    printf("ASCII key=%d, mouse (%d,%d)\n", key, x, y);
    if ( key == ' ')
    {
        printf("Space bar...\n");
    }
    if ( key == 27 )
    {
        glutDestroyWindow(glutGetWindow());
        exit(0);
    }
    if ( key == 'o' )
    {
        ortho = !ortho;
    }

    glutPostRedisplay();
}

void SpecialFunc( int key, int x, int y )
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
    }
    std::cout << "X:" << eye_x << " | Y:" << eye_y << " | Z:" << eye_z << std::endl;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGB);
    glutInitWindowSize(800, 600);
    if (glutCreateWindow("GLUT Template") < 1)
    {
        printf("glutCreateWindow() failed!\n");
    }
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(DrawingFunc);
    glutReshapeFunc(ReshapeFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(SpecialFunc);

    //glutMouseFunc(...Func);
    //glutMouseWheelFunc(...Func);
    //glutMotionFunc(...Func);

    InitFunc();
    glutMainLoop();

    return 0;
}



