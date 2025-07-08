#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion 
{
    public:
        Quaternion(float q0, float q1, float q2, float q3);
        Quaternion* mult(Quaternion * quat);
        Quaternion* scale(float scalar);
        Quaternion* add(Quaternion* quat);


    private:
        float q0, q1, q2, q3;
};

#endif