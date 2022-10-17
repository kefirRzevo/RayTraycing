#ifndef GENERAL_H
#define GENERAL_H

#include <SFML/Graphics.hpp>

#include "vector.h"

class Material
{
    public:
        Color matColor;
        float matKs;

        Material(Color col, float Ks):
            matColor(col), matKs(Ks) {};

        ~Material()
            {}
};

class Radiation
{
    public:
        Color radColor;
        float radKa;

        Radiation(Color col, float Ka):
            radColor(col), radKa(Ka) {};

        ~Radiation()
            {}
};

class Ray
{
    public:
        Vector rayStart;
        Vector rayFinish;

        Ray(Vector p1, Vector p2):
            rayStart(p1), rayFinish(p2) {};
        
        ~Ray()
            {}
};

class Color
{
    private:
        sf::Uint8 R;
        sf::Uint8 G;
        sf::Uint8 B;
        sf::Uint8 A;

    public:
        Color():
            R(0), G(0), B(0), A(0) {};

        Color(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue):
            R(Red), G(Green), B(Blue), A(255) {};

        Color(sf::Uint8 Red, sf::Uint8 Green, sf::Uint8 Blue, sf::Uint8 Alpha):
            R(Red), G(Green), B(Blue), A(Alpha) {};

        ~Color()
            {}

        float GetR()
            { return R; }

        float GetG()
            { return G; }

        float GetB()
            { return B; }

        Color& operator = (const Color& v)
        {
            this->R = v.R;
            this->G = v.G;
            this->B = v.B;
            return *this;
        }

        Color& operator += (const Color& v)
        {
            if((int)this->R + (int)v.R > 255)
                this->R = 255;
            else
                this->R += v.R;

            if((int)this->G + (int)v.G > 255)
                this->G = 255;
            else
                this->G += v.G;

            if((int)this->B + (int)v.B > 255)
                this->B = 255;
            else
                this->B += v.B;

            return *this;
        }

        Color& operator -= (const Color& v)
        {
            if((int)this->R - (int)v.R < 0)
                this->R = 255;
            else
                this->R -= v.R;

            if((int)this->G - (int)v.G < 0)
                this->G = 0;
            else
                this->G -= v.G;

            if((int)this->B - (int)v.B < 0)
                this->B = 0;
            else
                this->B -= v.B;

            return *this;
        }

        Color& operator *= (float k)
        {
            if(k*(float)this->R > 255)
                this->R = 255;
            else if(k*(float)this->R < 0)
                this->R = 0;
            else
                this->R*=k;

            if(k*(float)this->G > 255)
                this->G = 255;
            else if(k*(float)this->G < 0)
                this->G = 0;
            else
                this->G*=k;

            if(k*(float)this->B > 255)
                this->B = 255;
            else if(k*(float)this->B < 0)
                this->B = 0;
            else
                this->B*=k;

            return *this;
        }

        Color& operator /= (float k)
        {
            assert(k > EPSILON);
            if(((float)this->R)/k > 255)
                this->R = 255;
            else if(((float)this->R)/k < 0)
                this->R = 0;
            else
                this->R/=k;

            if(((float)this->G)/k > 255)
                this->G = 255;
            else if(((float)this->G)/k < 0)
                this->G = 0;
            else
                this->G/=k;

            if(((float)this->B)/k > 255)
                this->B = 255;
            else if(((float)this->B)/k < 0)
                this->B = 0;
            else
                this->B/=k;

            return *this;
        }

        Color operator + (Color v)
            { 
                return Color(*this)+=v; 
            }

        Color operator - (Color v)
            {   
                return Color(*this)-=v;
            }

        Color operator * (float k)
            {
                return Color(*this)*=k;
            }

        Color operator / (float k)
            {
                assert(k > EPSILON);
                return Color(*this)/=k;
            }

        friend Color Mul(Color c1, Color c2)
            {   
                return Color(c1.R * c2.R, 
                             c1.G * c2.G, 
                             c1.B * c2.B); 
            }
};

#endif //GENERAL_H
