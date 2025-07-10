#include "rotationHandler.h"

RotationHandler::RotationHandler(TimeTracker* timeTracker)
    : timeTracker(timeTracker) {}

void RotationHandler::update()
{
    Quaternion* angVel = cartesianToQuaternion(sensors->getGyroX(), sensors->getGyroY(), sensors->getGyroZ());
    
    orientation = orientation->mult
    (
        (angVel->scale(0.5*timeTracker->getTimeStep()))->exp()
    );
}

Quaternion* cartesianToQuaternion(float x, float y, float z)
{
    return new Quaternion
    (
        0,
        x,
        y,
        z
    );
}