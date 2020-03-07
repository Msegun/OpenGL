#include "Sphere.h"
#include <GL/freeglut.h>

Sphere::Sphere(float x, float y, float z, float r) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = r;
    this->colided = false;
}

void Sphere::Draw() {
    glPushMatrix();
    if(this->colided)
        glColor3f( 1, 0, 0 );
    else
        glColor3f( 0, 1, 0 );

    glTranslatef(this->x, this->y, this->z);
    glutWireSphere(this->radius, 32, 16);
    glPopMatrix();
}

void Sphere::MoveTo(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
