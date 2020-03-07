#include <GL/freeglut.h>
#include <iostream>

void Render(){
    glColor3f(1.0, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0, -1.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(0, 1.0);
    glEnd();
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World !");
    glutDisplayFunc(Render);
    glutMainLoop();
    return 0;
}