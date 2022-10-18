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
            if(i > WIDTH)
                i = WIDTH;

            if(j > HEIGHT)
                j = HEIGHT;
                
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
        std::vector<Light>  sceneLights;
        Camera              sceneCamera;

        bool ClosestIntersection(const Ray& incidentRay, Vector& closestIntersection, 
                                 Vector& closestNormal, Material& closestMaterial)
            {
                Vector intersectionPoint = Vector();
                Vector normal = Vector();
                float closestDistance = 0;

                for(size_t k = 0; k < sceneShapes.size(); k++)
                {
                    if(sceneShapes[k].CatchRay(incidentRay, intersectionPoint, normal))
                    {
                        float distance = (intersectionPoint - incidentRay.rayFinish).GetSquaredLen();
                        if(distance > closestDistance)
                        {
                            closestDistance = distance;
                            closestIntersection = intersectionPoint;
                            closestNormal = normal;
                            closestMaterial = sceneShapes[k].GetMaterial();
                        }
                    }
                }
                
                if(closestDistance == 0)
                    return false;

                return true;
            }
        
        bool RayReach(const Light& light, const Vector& point)
        {
            Ray incidentRay = Ray(light.lightPosition, point);
            Vector intersection = Vector();
            Vector normal = Vector();

            for(size_t k = 0; k < sceneShapes.size(); k++)
                if(sceneShapes[k].CatchRay(incidentRay, intersection, normal))
                    return false;

            return true;
        }

        Color GetIntensity(const Ray& incidentRay, size_t maxReflections)
            {
                Color color = Color();
                Material mat = Material();
                Vector normal = Vector();
                Vector intersectionPoint = Vector();
                Vector incident = incidentRay.rayFinish - incidentRay.rayStart;
                Vector reflected = 2 * Dot(normal, incident) * normal - incident;

                if(!(maxReflections && ClosestIntersection(incidentRay, 
                    intersectionPoint, normal, mat)))
                    return color;

                for(size_t k = 0; k < sceneLights.size(); k++)
                {
                    if(!RayReach(sceneLights[k], intersectionPoint))
                        continue;

                    Color lightColor = sceneLights[k].lightRadiation.radColor;
                    Vector light = sceneLights[k].lightPosition - intersectionPoint; 

/*light.Print();
normal.Print();
incident.Print();
reflected.Print();*/
                    float D = CosAngle(normal, incident);
                    float S =  std::pow(CosAngle(reflected, light), N_SPECULAR);

                    color += D * mat.matKd * Mul(lightColor, mat.matColor) + S * mat.matKs * lightColor;
                }

                return color; //+ mat.matKr * GetIntensity(Ray(intersectionPoint, 
                       //intersectionPoint + reflected), maxReflections - 1);
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
                    Ray incidentRay = Ray(sceneCamera.camPosition, scrPoint);

                    pixels[j * WIDTH + i] = GetIntensity(incidentRay, 3);
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
