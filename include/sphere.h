#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

class Sphere: public Shape
{
    private:
        float    sphereRadius;
        Vector   sphereCenter;
        Material sphereMat;

    public:
        Sphere(float r, Vector ctr, Material mat):
            sphereRadius(r), sphereCenter(ctr), sphereMat(mat) {};

        ~Sphere()
            {}

        Vector CatchRay(Ray* incidentRay, Ray* reflectedRay)
        {
            ;
        }
        
};

#endif //SPHERE_H
