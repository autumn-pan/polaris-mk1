#include "quaternion.h"
#include <cmath>

Quaternion::Quaternion(float q0, float q1, float q2, float q3)
    : q0(q0), q1(q1), q2(q2), q3(q3) {}

Quaternion * Quaternion::mult(Quaternion * q)
{
    return new Quaternion
    (
        this->q0 * q->q0 - this->q1 * q->q1 - this->q2 * q->q2 - this->q3 * q->q3,
        this->q0 * q->q1 + this->q1 * q->q0 + this->q2 * q->q3 - this->q3 * q->q2,
        this->q0 * q->q2 - this->q1 * q->q3 + this->q2 * q->q0 + this->q3 * q->q1,
        this->q0 * q->q3 + this->q1 * q->q2 - this->q2 * q->q1 + this->q3 * q->q0
    );
}

Quaternion * Quaternion::scale(float scalar)
{
    return new Quaternion(
        this->q0 * scalar,
        this->q1 * scalar,
        this->q2 * scalar,
        this->q3 * scalar
    );
}

Quaternion * Quaternion::add(Quaternion * q)
{
    return new Quaternion(
        q0 + q->q0,
        q1 + q->q1,
        q2 + q->q2,
        q3 + q->q3
    );
}

float Quaternion::magnitude()
{
    return std::sqrt(std::pow(q0,2) + std::pow(q1, 2) + std::pow(q2, 2) + std::pow(q3, 2));
}

Quaternion* Quaternion::normalize()
{
    float mag = this->magnitude();

    return new Quaternion
    (
        q0/mag,
        q1/mag,
        q2/mag,
        q3/mag
    );
}

// This function represents a rotation about nq essentially
Quaternion* Quaternion::exp()
{
    // Magnitude of the quaternion
    float mag = std::sqrt(q1*q1 + q2*q2 + q3*q3);
    
    // If the vector part has length 0, return to prevent divide by zzero error
    if(mag == 0.0f)
        return new Quaternion(1, 0, 0, 0);

    // This is the normalized quaternion
    Quaternion* nq = this->normalize();

    
    float scalar = std::cos(mag);
    float vectorScale = std::sin(mag)/mag;

    return new Quaternion
    (
        scalar,
        q1*vectorScale,
        q2*vectorScale,
        q3*vectorScale
    );
}


