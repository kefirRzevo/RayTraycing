#ifndef GENERAL_H
#define GENERAL_H

#include <SFML/Graphics.hpp>

#include "vector.h"

class Ray
{
    public:
        Vector rayStart;
        Vector rayDirection;

        Ray():
            rayStart(), rayDirection() {};

        Ray(Vector start, Vector direction):
            rayStart(start), rayDirection(direction) {};
        
        ~Ray()
            {}
};

static sf::Uint8 Clamp(int value)
{
    if(value > 255)
        return 255;
    else if(value < 0)
        return 0;
    else
        return value;
}

class Color
{
    private:
        sf::Uint8 R;
        sf::Uint8 G;
        sf::Uint8 B;
        sf::Uint8 A;

    public:
        Color():
            R(0), G(0), B(0), A(255) {};

        Color(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue):
            R(Red), G(Green), B(Blue), A(255) {};

        Color(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue, sf::Uint8 Alpha):
            R(Red), G(Green), B(Blue), A(Alpha) {};

        ~Color()
            {}

        float GetR() const 
            { return R; }

        float GetG() const
            { return G; }

        float GetB() const
            { return B; }

        float GetA() const
            { return A; }

        Color& operator = (const Color& v)
        {
            this->R = v.R;
            this->G = v.G;
            this->B = v.B;
            return *this;
        }

        Color& operator += (const Color& v)
        {
            this->R += Clamp(v.R);
            this->G += Clamp(v.G);
            this->B += Clamp(v.B);
            return *this;
        }

        Color& operator -= (const Color& v)
        {
            this->R -= Clamp(v.R);
            this->G -= Clamp(v.G);
            this->B -= Clamp(v.B);
            return *this;
        }

        Color& operator *= (const float k)
        {
            this->R *= Clamp(this->R * k);
            this->G *= Clamp(this->G * k);
            this->B *= Clamp(this->B * k);
            return *this;
        }

        Color& operator /= (float k)
        {
            assert(k > EPSILON);
            this->R *= Clamp(this->R / k);
            this->G *= Clamp(this->G / k);
            this->B *= Clamp(this->B / k);
            return *this;
        }

        friend Color operator + (const Color& c1, const Color& c2)
            { 
                return Color(Clamp(c1.R + c2.R), Clamp(c1.G + c2.G), Clamp(c1.B + c2.B));
            }

        friend Color operator - (const Color& c1, const Color& c2)
            {   
                return Color(Clamp(c1.R - c2.R), Clamp(c1.G - c2.G), Clamp(c1.B - c2.B));
            }

        friend Color operator * (const Color& c, const float k)
            {
                return Color(Clamp(c.R * k), Clamp(c.G * k), Clamp(c.B * k));
            }

        friend Color operator * (const float k, const Color& c)
            {
                return Color(Clamp(c.R * k), Clamp(c.G * k), Clamp(c.B * k));
            }

        friend Color operator / (const Color& c, const float k)
            {
                assert(k > EPSILON);
                return Color(Clamp(c.R / k), Clamp(c.G / k), Clamp(c.B / k));
            }

        friend Color Mul(const Color& c1, const Color& c2)
            {   
                return Color(Clamp(c1.R * c2.R), Clamp(c1.G * c2.G), Clamp(c1.B * c2.B)); 
            }

        void Print() const
            { 
                printf("%hhu %hhu %hhu\n", R, G, B); 
            }
};

class Material
{
    public:
        Color matColor;
        float matKd;
        float matKs;
        float matKr;

        Material():
            matColor(Color()), matKd(0), matKs(0), matKr(0) {};

        Material(Color col, float Kd, float Ks, float Kr):
            matColor(col), matKd(Kd), matKs(Ks), matKr(Kr) {};

        ~Material()
            {}
};

class Radiation
{
    public:
        Color radColor;
        float radKa;

        Radiation():
            radColor(Color()), radKa(0) {};

        Radiation(Color col, float Ka):
            radColor(col), radKa(Ka) {};

        ~Radiation()
            {}
};

#endif //GENERAL_H
