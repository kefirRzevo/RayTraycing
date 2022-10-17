#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

#include "config.h"

class Vector
{
    protected:
        float x;
        float y;
        float z;

    public:
        Vector():
            x(0), y(0), z(0) {};

        Vector(float anX, float anY, float anZ):
            x(anX), y(anY), z(anZ) {};

        ~Vector()
            {}

        float GetX()
            { return x; }

        float GetY()
            { return y; }

        float GetZ()
            { return z; }

        float GetLen()
            { return std::sqrt(x*x+y*y+z*z); }

        float GetSquaredLen()
            { return x*x+y*y+z*z; }

        Vector& operator = (const Vector& v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            return *this;
        }

        Vector& operator += (const Vector& v)
        {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            return *this;
        }

        Vector& operator -= (const Vector& v)
        {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            return *this;
        }

        Vector& operator *= (float k)
        {
            this->x *= k;
            this->y *= k;
            this->z *= k;
            return *this;
        }

        Vector& operator /= (float k)
        {
            assert(k < EPSILON);
            this->x /= k;
            this->y /= k;
            this->z /= k;
            return *this;
        }

        Vector operator + (Vector v)
            { 
                return Vector(*this)+=v; 
            }

        Vector operator - (Vector v)
            {   
                return Vector(*this)-=v;
            }

        Vector operator * (float k)
            {
                return Vector(*this)*=k;
            }

        Vector operator / (float k)
            {
                assert(k > EPSILON);
                return Vector(*this)/=k;
            }

        Vector Normalize()
            {
                float len = this->GetLen();
                assert(len != 0);
                return *this / len; 
            } 

        friend Vector Cross(Vector v1, Vector v2)
            {   
                return Vector(v1.y * v2.z - v1.z * v2.y, 
                              v1.z * v2.x - v1.x * v2.z, 
                              v1.x * v2.y - v1.y * v2.x); 
            }

        friend float Dot(Vector v1, Vector v2)
            { 
                return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
            }

        friend float CosAngle(Vector v1, Vector v2)
            {
                float len1 = v1.GetLen();
                float len2 = v2.GetLen();
                assert(len1 != 0 && len2 != 0);
                return Dot(v1, v2)/(len1*len2); 
            }
};

#endif  //VECTOR_H
