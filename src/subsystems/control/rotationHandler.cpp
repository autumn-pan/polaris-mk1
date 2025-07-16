#include "rotationHandler.h"

RotationHandler::RotationHandler(TimeTracker* timeTracker)
    : timeTracker(timeTracker) {}


void RotationHandler::update()
{
    // Retrieve angular velocity directly from the gyros
    Quaternion* angVel = cartesianToQuaternion(sensors->getGyroX(), sensors->getGyroY(), sensors->getGyroZ());

    float dt = timeTracker->getTimeStep()/1000;

    // Optimally integrate the quaternions using an exponential mapping
    orientation = orientation->mult((angVel->scale(0.5*dt))->exp());

    delete(angVel);
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

Quaternion* RotationHandler::getOrientation()
{
    return orientation;
}