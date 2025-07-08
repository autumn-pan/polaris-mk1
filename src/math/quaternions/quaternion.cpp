#include "quaternion.h"

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