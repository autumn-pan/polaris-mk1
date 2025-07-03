#include "motor.h"
#include "massTracker.h"

MassTracker::MassTracker(Motor * motor1, Motor * motor2, float rocketMass)
    : motor1(motor1), motor2(motor2), rocketMass(rocketMass)
    {
        mass = motor1->getTotalMass() + motor2->getTotalMass() + rocketMass;
    }

void MassTracker::update()
{
    motor1->update();
    motor2->update();
    mass = motor1->getTotalMass() + motor2->getTotalMass() + rocketMass;
}

float MassTracker::getMass()
{
    return mass;
}