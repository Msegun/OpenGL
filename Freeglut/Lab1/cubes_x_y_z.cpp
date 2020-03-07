#include <iostream>
#include <GL/freeglut.h>

float eye_x = 1.5;
float eye_y = 0;
float eye_z = 1.5;

float rot = 0.0;

void drawAxis(){
    glBegin(GL_LINES);
    // x aix
    glColor3f(1, 1, 0);
    glVertex3f(-4.0, 0.0f, 0.0f);
    glVertex3f(4.0, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    // y aix
    glColor3f(1, 1, 0);
    glVertex3f(0.0, 4.0f, 0.0f);
    glVertex3f(0.0, -4.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    // z aix
    glColor3f(1, 1, 0);
    glVertex3f(0.0, 0.0f, 4.0f);
    glVertex3f(0.0, 0.0f, -4.0f);
    glEnd();
}

void drawCube(float x, float y, float z, float scale, char rotChar)
{
    glPushMatrix();
    if (rotChar == 'y'){
        glRotatef(rot, 0,1,0);
    }
    if (rotChar == 'x'){
        glRotatef(rot, 1,0,0);
    }
    if (rotChar == 'z'){
        glRotatef(rot, 0,0,1);
    }

    glBegin(GL_POLYGON); // Top face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x + scale, y + scale, z - scale);
    glVertex3f(x - scale, y + scale, z - scale);
    glVertex3f(x - scale, y + scale, z + scale);
    glVertex3f(x + scale, y + scale, z + scale);
    glEnd();

    glBegin(GL_POLYGON); // Bottom face
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(x + scale, y - scale, z + scale);
    glVertex3f(x - scale, y - scale, z + scale);
    glVertex3f(x - scale, y - scale, z - scale);
    glVertex3f(x + scale, y - scale, z - scale);
    glEnd();

    glBegin(GL_POLYGON); // Front face
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x + scale, y + scale, z + scale);
    glVertex3f(x - scale, y + scale, z + scale);
    glVertex3f(x - scale, y - scale, z + scale);
    glVertex3f(x + scale, y - scale, z + scale);
    glEnd();

    glBegin(GL_POLYGON); // Back face
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(x + scale, y - scale, z - scale);
    glVertex3f(x - scale, y - scale, z - scale);
    glVertex3f(x - scale, y + scale, z - scale);
    glVertex3f(x + scale, y + scale, z - scale);
    glEnd();

    glBegin(GL_POLYGON); // Left face
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(x - scale, y + scale, z + scale);
    glVertex3f(x - scale, y + scale, z - scale);
    glVertex3f(x - scale, y - scale, z - scale);
    glVertex3f(x - scale, y - scale, z + scale);
    glEnd();

    glBegin(GL_POLYGON); // Right face
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex3f(x + scale, y + scale, z - scale);
    glVertex3f(x + scale, y + scale, z + scale);
    glVertex3f(x + scale, y - scale, z + scale);
    glVertex3f(x + scale, y - scale, z - scale);
    glEnd();
    glPopMatrix();
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
            0,0,0,
            0,1,0
    );

    drawAxis();

    drawCube(0, 0, 0, 0.2, ' ');
    // X
    drawCube(1, 0, 0, 0.3, 'x');
    drawCube(-1, 0, 0, 0.3, 'x');

    // Y
    drawCube(0, 1, 0, 0.3, 'y');
    drawCube(0, -1, 0, 0.3, 'y');

    // Z
    drawCube(0, 0, 1, 0.3, 'z');
    drawCube(0, 0, -1, 0.3, 'z');
    rot += 0.1;
    if (rot > 360)
        rot = 0;
    glFlush();
}

void ReshapeFunc (int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 8.0/6.0, 0.1, 20);
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
    glutInitDisplayMode ( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
    glutInitWindowSize(800, 600);
    if (glutCreateWindow("GLUT Template") < 1)
    {
        printf("glutCreateWindow() failed!\n");
    }
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(DrawingFunc);
    glutReshapeFunc(ReshapeFunc);
    glutSpecialFunc(SpecialFunc);
    glutIdleFunc(DrawingFunc);
    glutMainLoop();

    return 0;
}



