#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>

#include "myvector.h"

class Scene
{
    private:
        std::vector<Shape* > shapes;
        std::vector<Light>   lights;
        Camera               camera;

    public:

        Scene(Camera cam):
            camera(cam) {};

        ~Scene()
            {}

        int Draw(sf::RenderWindow window);

        int Add(Shape* shape);
        int Add(Light  light);

};


class Shape
{
    public:


};

class Material
{
    Color col;
    float 
};

class 

class Sphere: public Shape
{
    private:
        Vector sphereCenter;
        Vector sphereColor;

        float  sphereRadius;
        float  sphereKd;
        float  sphereKs;

    public:
        Sphere(Vector ctr, Vector col, float r, float Kd, float Ks):
            sphereCenter(ctr), sphereColor(col), sphereRadius(r),
            sphereKd(Kd), sphereKs(Ks){};

        ~Sphere()
            {}

        
};

class Light
{
    private:
        Vector lightPosition;
        float  lightRadius;
        Color  lightColor;
        float  lightKa;

    public:
        Light(Vector pos, Vector col, float Ka):
            lightPosition(pos), lightColor(col), ligthKa(Ka){};
        
        ~Light()
            {}
};

class Camera
{
    private:
        Vector camPosition;
        Vector scrCenter;
        float  scrWidth;
        float  scrHeight;  
    
    public:
        Camera(Vector pos, Vector ctr, float w, float h)
            {
                camPosition = pos;
                scrCenter   = ctr;
                scrWidth    = w;
                scrHeight   = h;
            }

        ~Camera()
            {}

        unsigned int getWidth()
            { return (unsigned int)scrWidth; }

        unsigned int getHeight()
            { return (unsigned int)scrHeight; }
};


class Pixel
{
    private:
        sf::Uint8 R;
        sf::Uint8 G;
        sf::Uint8 B;
        sf::Uint8 A;

    public:
        Pixel():
            R(0), G(0), B(0), A(0) {};

        Pixel(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue):
            R(Red), G(Green), B(Blue), A(255) {};

        Pixel(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue, sf::Uint8 Alpha):
            R(Red), G(Green), B(Blue), A(Alpha) {};

        ~Pixel()
            {}

        Color PixToVector(Pixel pxl)
            { return Color(pxl.R/255, pxl.G/255, pxl.B/255); }
};

//bool LineCrossSphere(Vector linepoint1, Vector linepoint2, 
//                     float radius, Vector spherecenter, Vector& nearest_crosspoint);

//Vector CountIntensity(Vector pixel, int n_spheres, 
//                                  Sphere* spheres, Lamp lamp, Camera camera);

//Pixel VectorToPix(Vector v, float Alpha);

#endif  //RENDER_H
