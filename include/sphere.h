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

        bool CatchRay(const Ray& ray, Vector& intersectionPoint, Vector& normal)
        {
            Vector start = ray.rayStart;
            Vector direction = ray.rayDirection;
            Vector center = sphereCenter;

            float FS  = Dot(direction, direction);
            float FCS = Dot(direction, start - center);
            float SC  = Dot(start - center, start - center);

            float a = FS, b = 2 * FCS, c = SC - sphereRadius * sphereRadius;
            float D = b * b - 4 * a * c;

            if(D < EPSILON)
                return false;

            float t1 = (-b - std::sqrt(D)) / (2 * a);
            float t2 = (-b + std::sqrt(D)) / (2 * a);

            if(t1 < 0)
                return false;

            intersectionPoint = start + t1 * direction;
            normal = GetNormal(intersectionPoint);

            return true;
        }

        Vector GetNormal(Vector point)
        {
            return Vector(point - sphereCenter).Normalize();
        }

        Material GetMaterial() const
        { 
            return sphereMat;
        }
};

#endif //SPHERE_H
