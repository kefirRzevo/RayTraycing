#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

#include "config.h"

class Vector
{
    private:
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

        float GetX() const
            { return x; }

        float GetY() const
            { return y; }

        float GetZ() const
            { return z; }

        float GetLen() const
            { return std::sqrt(x * x + y * y + z * z); }

        float GetSquaredLen() const
            { return x * x + y * y + z * z; }

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

        friend Vector operator + (const Vector& v1, const Vector& v2)
            { 
                return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); 
            }

        friend Vector operator - (const Vector& v1, const Vector& v2)
            {   
                return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); 
            }

        friend Vector operator * (const Vector& v, float k)
            {
                return Vector(v.x * k, v.y * k, v.z * k); 
            }

        friend Vector operator * (float k, const Vector& v)
            {
                return Vector(v.x * k, v.y * k, v.z * k); 
            }

        friend Vector operator / (const Vector& v, float k)
            {
                assert(k > EPSILON);
                return Vector(v.x / k, v.y / k, v.z / k); 
            }

        Vector Normalize()
            {
                float len = this->GetLen();
                assert(len != 0);
                return *this / len;
            } 

        friend Vector Cross(const Vector& v1, const Vector& v2)
            {   
                return Vector(v1.y * v2.z - v1.z * v2.y, 
                              v1.z * v2.x - v1.x * v2.z, 
                              v1.x * v2.y - v1.y * v2.x); 
            }

        friend float Dot(const Vector& v1, const Vector& v2)
            { 
                return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
            }

        friend float CosAngle(const Vector& v1, const Vector& v2)
            {
                float len1 = v1.GetLen();
                float len2 = v2.GetLen();
                assert(len1 != 0 && len2 != 0);
                return Dot(v1, v2) / (len1 * len2); 
            }

        void Print() const
            { 
                printf("%8.4lf %8.4lf %8.4lf\n", x, y, z);                 
            }
};

#endif  //VECTOR_H
