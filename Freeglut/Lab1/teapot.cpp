#include <stdio.h>
#include <GL/freeglut.h>

float rot = 0.0;

void drawSpinningTeacup(float x, float y, float z, float size){
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rot, 0, 1, 0);
    glutWireTeacup(size);
    glPopMatrix();
}

void DrawingFunc(void)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, 1.7, 0.1, 20);

    // 3. Set the camera position
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt(4.0,4.0,4, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 4. Clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (rot > 360)
        rot = 0;

    // 5. Drawing
    // Translate (move away) the center of The Coordinate System (TCS)
    glTranslatef(0.0, 0.0, 0.0);

    glScalef(2.0, 2.0, 2.0);
    glColor3f(0, 1, 0);
    glutWireTeapot(1.0);

    glColor3f(0, 0, 1);

    for(int i = 0; i < 7; i++){

    }
    glRotatef(-rot+50, 0, 1, 0);
    drawSpinningTeacup(2,0,0, 0.5);
    drawSpinningTeacup(-2, 0, 0, 0.5);
    drawSpinningTeacup(0, 0, 2, 0.5);
    drawSpinningTeacup(0, 0, -2, 0.5);

    rot += 0.1;
    glutSwapBuffers();
}

void InitFunc()
{
//    glClearColor( 0.2, 0.2, 0.2, 1 );
    glShadeModel ( GL_FLAT );
}

void ReshapeFunc (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc( unsigned char key, int x, int y )
{
    if ( key == 'p') {  }

    glutPostRedisplay();
}

void SpecialFunc( int key, int x, int y )
{
    switch( key )
    {
        case GLUT_KEY_LEFT:
            rot -= 5.0;
            break;

        case GLUT_KEY_RIGHT:
            rot += 5.0;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(960, 540);

    if (glutCreateWindow("First cube ever") < 1)
    {
        printf("glutCreateWindow() failed!\n");
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(DrawingFunc);
    glutIdleFunc(DrawingFunc);
    glutReshapeFunc(ReshapeFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutSpecialFunc(SpecialFunc);

    InitFunc();
    glutMainLoop();

    return 0;
}


