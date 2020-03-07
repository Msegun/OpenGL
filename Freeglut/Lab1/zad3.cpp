#include <GL/freeglut.h>
#include <random>

void Render() {
    glColor3f(1.0, 0, 0);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-20,20);
    for(int i = 0; i<20; i++) {

        float x1 = distribution(generator) % 20 / 20.0;
        float x2 = distribution(generator) % 20 / 20.0;
        float y1 = distribution(generator) % 20 / 20.0;
        float y2 = distribution(generator) % 20 / 20.0;

        glBegin(GL_LINE_STRIP);

        glColor3f(rand() % 20 / 20.0, rand() % 20 / 20.0, rand() % 20 / 20.0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);

        glVertex2f(x1, y1);

        glEnd();
    }
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