#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>

#include "vector.h"
#include "general.h"
#include "sphere.h"

/*
class Shape
{
    public:
};
*/

class Light
{
    public:
        Vector    lightPosition;
        Radiation lightRadiation;

        Light(Vector pos, Radiation rad):
            lightPosition(pos), lightRadiation(rad){};

        ~Light()
            {}
};

class Camera
{
    public:
        Vector camPosition;
        Vector scrCenter;
        Vector scrWidth; 
        Vector scrHeight;

        Camera(Vector pos, Vector ctr, Vector w, Vector h):
            camPosition(pos), scrCenter(ctr), scrWidth(w), scrHeight(h) {};

        ~Camera()
            {}

        Vector GetScreenPoint(size_t i, size_t j) const
        {
            Vector scrPoint = scrCenter;
            scrPoint += (2*(float)i/(float)WIDTH - 1)*(scrWidth - scrCenter);
            scrPoint += (2*(float)j/(float)HEIGHT - 1)*(scrHeight - scrCenter);

            return scrPoint;
        }
};

class Scene
{
    private:
        std::vector<Sphere> sceneShapes;
        std::vector<Light> sceneLights;
        Camera sceneCamera;

        bool GetIntersection(const Ray& ray, Vector& closestIntersection, 
                             Material& closestMaterial, Vector& closestNormal)
            {
                Vector start = ray.rayStart;
                Vector intersection = Vector();
                Vector normal = Vector();
                float closestDistance = 0;

                for(size_t k = 0; k < sceneShapes.size(); k++)
                {
                    if(sceneShapes[k].CatchRay(ray, intersection, normal))
                    {
                        float distance = (intersection - start).GetSquaredLen();

                        if(!closestDistance || closestDistance > distance - EPSILON)
                        {
                            closestDistance = distance;
                            closestNormal = normal;
                            closestMaterial = sceneShapes[k].GetMaterial();
                            closestIntersection = intersection;
                        }
                    }
                }

                if(closestDistance < EPSILON)
                    return false;

                return true;
            }

        bool LightReach(Vector lightPosition, const Vector& point)
        {
            Vector direction = (point - lightPosition).Normalize();
            Vector shiftPoint = point - direction * EPSILON;
            Ray incidentRay = Ray(lightPosition, direction);

            Vector intersectionPoint = Vector();
            Vector tempNormal = Vector();

            float shiftDistance = (lightPosition - shiftPoint).GetSquaredLen();

            for(size_t k = 0; k < sceneShapes.size(); k++)
                if(sceneShapes[k].CatchRay(incidentRay, intersectionPoint, tempNormal))
                {
                    float distance = (lightPosition - intersectionPoint).GetSquaredLen();
                    if(distance < shiftDistance)
                        return false;
                }

            return true;
        }

        Color GetColor(const Ray& incidentRay, size_t maxReflections)
            {
                Color color = Color();

                if(!maxReflections)
                    return color;

                Material mat = Material();
                Vector normal = Vector();
                Vector intersection = Vector();

                if(!GetIntersection(incidentRay, intersection, mat, normal))
                    return color;

                Vector incident  = incidentRay.rayDirection;
                Vector reflected = incident - 2*Dot(normal, incident)*normal;

                for(size_t k = 0; k < sceneLights.size(); k++)
                {
                    //if(!LightReach(sceneLights[k].lightPosition, intersection))
                      //  continue;

                    Color  lightColor = sceneLights[k].lightRadiation.radColor;
                    Vector light = intersection - sceneLights[k].lightPosition; 

                    float D = CosAngle(normal, -1*incident);
                    float S = std::pow(CosAngle(reflected, light), N_SPECULAR);

                    color += fabs(D) * mat.matKd * Mul(lightColor, mat.matColor) +
                             S * mat.matKs * lightColor;
                }

                return color;//*(1-mat.matKr) + mat.matKr * GetColor(Ray(intersection, 
                        //reflected), maxReflections - 1);
            }

    public:
        Scene(const Camera& camera):
            sceneCamera(camera) {};

        ~Scene()
            {}

        void Draw(Color* pixels)
        {
            for(size_t i = 0; i < WIDTH; i++)
                for(size_t j = 0; j < HEIGHT; j++)
                {
                    Vector scrPoint = sceneCamera.GetScreenPoint(i, j);
                    Vector direction = scrPoint - sceneCamera.camPosition;

                    Ray incidentRay = Ray(sceneCamera.camPosition, direction);

                    pixels[j * WIDTH + i] = GetColor(incidentRay, 5);
                }
        }

        void AddSphere(Sphere sphere)
        {
            sceneShapes.push_back(sphere);
        }

        void AddLight(Light light)
        {
            sceneLights.push_back(light);
        }
};

#endif  //RENDER_H
