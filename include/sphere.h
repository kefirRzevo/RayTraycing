#ifndef SPHERE_H
#define SPHERE_H

#include "general.h"
#include "vector.h"

class Sphere
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

        Material GetMaterial() const
            { return sphereMat; }

        bool CatchRay(const Ray& incidentRay, Vector& intersectionPoint, Vector& normal)
        {
            float FS  = Dot(incidentRay.rayFinish - incidentRay.rayStart, 
                            incidentRay.rayFinish - incidentRay.rayStart);
            float FCS = Dot(incidentRay.rayFinish - incidentRay.rayStart, 
                            incidentRay.rayStart - sphereCenter);
            float SC  = Dot(incidentRay.rayStart - sphereCenter, 
                            incidentRay.rayStart - sphereCenter);

            float a = FS, b = 2 * FCS, c = SC - sphereRadius * sphereRadius;
            float D = b * b - 4 * a * c;

            if(D < 0)
                return false;

            float t1 = (-b - std::sqrt(D)) / (2 * a);
            float t2 = (-b + std::sqrt(D)) / (2 * a);

            if(t2 < 0)
                return false;

            if(t1 < 0)
                t1 = t2;

            intersectionPoint = incidentRay.rayStart + t1 * \
                        (incidentRay.rayFinish - incidentRay.rayStart);

            normal = (intersectionPoint - sphereCenter).Normalize();

            return true;
        }
};

#endif //SPHERE_H
