#include "Motor.h"

// constructor for the motor class
Motor::Motor(float burnTime, float motorMass, float propellantMass, TimeTracker timeTracker)
    : burnTime(burnTime), motorMass(motorMass), propellantMass(propellantMass), timeTracker(timeTracker) {}

// Marks the motor as "burning"
void Motor::burn()
{
    isBurning = true;
    burnStartTime = timeTracker.getTime();
}

void Motor::update()
{
    
}