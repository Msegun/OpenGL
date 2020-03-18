#include <GL/freeglut.h>
#include <random>

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

// CHYBA O TO CHODZI : P
void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-120,120);

    glFrontFace(GL_CW);
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 8; i++){
        glColor3f(rand() % 20 / 120.0, rand() % 20 / 120.0, rand() % 20 / 120.0);
        double x = distribution(generator)  % 120;
        double y = distribution(generator)  % 120;
        glVertex2f(x, y);
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