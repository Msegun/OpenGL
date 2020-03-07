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


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-120,120);
    float center_x = 0;
    float center_y = 0;

    float p1_x = 50;
    float p1_y = 50;
    float p2_x = 80;
    float p2_y = 80;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0, 0);

    glVertex2f(center_x, center_y);
    glVertex2f(p1_x, p1_y);
    glVertex2f(p2_x, p2_y);
    glVertex2f(p2_x, -p1_y);
    glVertex2f(-p2_x, -p2_y);
    glVertex2f(-p1_x, p1_y);
    glVertex2f(-p1_x, p2_y);

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