#include <GL/freeglut.h>
#include <cmath>
#include <random>
#include "iostream"

#define EULER 2.718281

void Init(){
    glClearColor(0.2, 0.2, 0.2, 1);
    glShadeModel(GL_SMOOTH);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glLineWidth(1.0);
    glPointSize(2.0);
}

void Reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluOrtho2D(-120, 120, -120, 120);
};


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);

    // a) okrąg
    glBegin(GL_POINTS);
    float angle;
    for (angle = 0; angle < 360; angle += 1) {
        float x, y;
        x = 10 * std::cos(angle);
        y = 10 * std::sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // b) Parabola funkcja np y=x^2 bo jestem leniwy
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    float x = -120;
    while (x < 120) {
        float y = std::pow(x, 2);
        glVertex2f(x, y);
        x += 0.5;
    }
    glEnd();

    // c) Spirala
    float a = 1, b = 1;
    float theta = 0;
    glBegin(GL_LINE_STRIP);
    while (theta < 360){
        glColor3f(0, 0, 1);
        float r = a + b * theta;
        x = r * std::cos(theta);
        float y = r * std::sin(theta);
        glVertex2f(x, y);
        theta+=0.2;
    }
    glEnd();

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World !");
    glutDisplayFunc(Render);
    glutReshapeFunc(Reshape);
    Init();
    glutMainLoop();
    return 0;
}