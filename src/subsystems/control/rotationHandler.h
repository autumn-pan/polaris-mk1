#ifndef ROTATION_HANDLER_H
#define ROTATION_HANDLER_H
#include "filter.h"
#include "../../math/quaternions/quaternion.h"
#include "../../math/linalg/vector3.h"
#include "./timing/timeTracker.h"

class RotationHandler
{
    public:
        RotationHandler(TimeTracker* timeTracker);
        void update(Quaternion* angVel);

    private:
        Quaternion* orientation;
        TimeTracker* timeTracker;
};
#endif