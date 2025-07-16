#ifndef MASS_TRACKER_H
#define MASS_TRACKER_H
#include "motor.h"
class MassTracker
{
    public:
        MassTracker(Motor * motor1, Motor * motor2, float rocketMass);
        void update();
        float getMass();

        Motor * getMotor1();
        Motor * getMotor2();
    private:
        float rocketMass;
        float mass;
        Motor * motor1;
        Motor * motor2;

};
#endif