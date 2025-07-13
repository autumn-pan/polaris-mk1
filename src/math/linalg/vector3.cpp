#include "vector3.h"
#include <cmath>

Vector3::Vector3()
    : x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z) {}

Vector3 * Vector3::add(Vector3* v)
{
    return new Vector3
    (
        x + v->x,
        y + v->y,
        z + v->z
    );
}

Vector3 * Vector3::sub(Vector3* v)
{
    return new Vector3
    (
        x - v->x,
        y - v->y,
        z - v->z
    );
}

Vector3 * Vector3::scale(float scalar)
{
    return new Vector3
    (
        x*scalar,
        y*scalar,
        z*scalar
    );
}

float Vector3::dot(Vector3 * v)
{
    return x*v->x + y*v->y + z*v->z;
}

float Vector3::norm()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

float Vector3::getX() {return x;}
float Vector3::getY() {return y;}
float Vector3::getZ() {return z;}
