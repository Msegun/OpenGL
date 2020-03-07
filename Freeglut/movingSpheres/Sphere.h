#ifndef MOVINGSPHERES_SPHERE_H
#define MOVINGSPHERES_SPHERE_H

class Sphere {
public:
    float x, y, z;
    float radius;
    bool colided;
    Sphere (float x, float y, float z, float r);
    void Draw();
    void MoveTo(float x, float y, float z);
};


#endif //MOVINGSPHERES_SPHERE_H
