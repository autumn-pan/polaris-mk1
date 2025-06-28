#ifndef MOTOR_H
#define MOTOR_H
#include "../../timeTracker.h"
// The Motor Class keeps track of motor information, like mass, burntime, etc.
// Propellant mass linearly decreases when the motor is burning, but this can be improved to follow a closer polynomial approximation instead.
class Motor
{
    public:
        Motor(float burnTime, float motorMass, float propellantMass, TimeTracker timeTracker);
        void burn();
        void update();

        // getter functions
        bool isBurning();
        bool burnedOut();

        float getTotalMass();
        float getPropellantMass();
        float getMotorMass();
    private:
        bool isBurning = false;
        bool burnedOut = false;

        float burnTime;
        float burnStartTime;
        float totalMass;
        float propellantMass;
        float motorMass; // mass of motor w/o propellant

        TimeTracker timeTracker;
};
#endif