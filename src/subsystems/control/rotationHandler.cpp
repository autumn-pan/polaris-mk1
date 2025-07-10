#include "rotationHandler.h"

RotationHandler::RotationHandler(TimeTracker* timeTracker)
    : timeTracker(timeTracker) {}

void RotationHandler::update(Quaternion* angVel)
{
    orientation = orientation->mult
    (
        (angVel->scale(0.5*timeTracker->getTimeStep()))->exp()
    );
}