#ifndef MOTOR_H
#define MOTOR_H
#include "../../timing/timeTracker.h"
// The Motor Class keeps track of motor information, like mass, burntime, etc.
// Propellant mass linearly decreases when the motor is burning, but this can be improved to follow a closer polynomial approximation instead.
class Motor
{
    public:
        Motor(float burnTime, float motorMass, float propellantMass, TimeTracker timeTracker);
        bool burn();
        bool update();

        void jettison();

        // getter functions
        bool getBurning();
        bool getBurnedOut();

        float getTotalMass();
        float getPropellantMass();
        float getMotorMass();
        float getBurnTime();

        bool jettisoned();
    private:
        bool isBurning = false;
        bool burnedOut = false;

        bool jettisoned = false;

        float burnTime;
        float burnStartTime;
        float totalMass;
        float propellantMass;
        float motorMass; // mass of motor w/o propellant

        float propellantBurnRate;

        TimeTracker timeTracker;
};
#endif