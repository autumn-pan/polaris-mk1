#include "motor.h"

// constructor for the motor class
Motor::Motor(float burnTime, float motorMass, float propellantMass, TimeTracker timeTracker)
    : burnTime(burnTime), motorMass(motorMass), propellantMass(propellantMass), timeTracker(timeTracker) 
    {
        propellantBurnRate = propellantMass/burnTime;
    }


// Marks the motor as "burning"
bool Motor::burn()
{
    // Ensure that the motor can still be burned
    if (burnedOut)
        return false;

    isBurning = true;
    burnStartTime = timeTracker.getTime();

    return true;
}

// Call this function every cycle
bool Motor::update()
{
    // If the rocket has been jettisoned, no further action can be done
    if (jettisoned)
        return false;

    int time = timeTracker.getTime();

    // Check for whether the motor is burning
    if ((time - burnStartTime) > burnTime)
        isBurning = false;
    else // Update propellant mass if burning
        propellantMass -= timeTracker.getElapsedTime()*propellantBurnRate;

    // Update total mass
    totalMass = propellantMass + motorMass;
    return true;
}

void Motor::jettison()
{
    jettisoned = true;
    totalMass = 0;
}

// Getter functions
bool Motor::getBurning() {return isBurning;}
bool Motor::getBurnedOut() {return burnedOut;}
float Motor::getPropellantMass() {return propellantMass;}
float Motor::getTotalMass() {return totalMass;}
float Motor::getMotorMass() {return motorMass;}
float Motor::getBurnTime() {return burnTime;}
