#ifndef ROTATION_HANDLER_H
#define ROTATION_HANDLER_H
#include "./sensors/sensors.h"
#include "../../math/quaternions/quaternion.h"
#include "../../math/linalg/vector3.h"
#include "./timing/timeTracker.h"

class RotationHandler
{
    public:
        RotationHandler(TimeTracker* timeTracker);
        void update();

    private:
        Quaternion* orientation;
        TimeTracker* timeTracker;    
        SensorStack* sensors;
};

Quaternion* cartesianToQuaternion(float x, float y, float z);

#endif