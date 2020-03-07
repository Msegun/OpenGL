#include <cmath>
#include "iostream"
#include <GL/freeglut.h>
#include "Sphere.h"

float rotation_angle = 0.0;
Sphere a(-0.5, 0, 0, 0.2);
Sphere b(0.5, 0, 0.3, 0.3);
Sphere c(0, 0.7, 0, 0.4);


void keyboard(unsigned char key, int x, int y) {
    if(key == 'w')
        c.y += 0.02;
    if(key == 's')
        c.y -= 0.02;
    if(key == 'd')
        c.x += 0.02;
    if(key == 'a')
        c.x -= 0.02;
}

void resize(int w, int h){
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1000, 1000);
}

bool sphere_colision(Sphere a, Sphere b){
    float r_x = a.x - b.x;
    float r_y = a.y - b.y;
    float r_z = a.z - b.z;
    float distance = std::sqrt(r_x * r_x + r_y * r_y + r_z * r_z);
    return distance <= a.radius + b.radius;
}

void colisionCheck(){
    bool ab = sphere_colision(a, b);
    bool bc = sphere_colision(b, c);
    bool ac = sphere_colision(a, c);
    a.colided = ab || ac;
    b.colided = ab || bc;
    c.colided = ac || bc;
};


void draw(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    if(rotation_angle == 360.0)
        rotation_angle = 0;
    // Reset Transformation
    glLoadIdentity();
    gluLookAt(0, 0.5, 1,0, 0, 0,0, 1, 0);
    glTranslatef(0, 0, 1);
    glRotatef(rotation_angle, 0.0, 1.0, 0.0);
    colisionCheck();

//    c.MoveTo(c.x, c.y-0.01, c.z);

    a.Draw();
    b.Draw();
    c.Draw();
    rotation_angle += 0.5;
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    glutCreateWindow("Moving Spheres");

    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutIdleFunc(draw);

    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}