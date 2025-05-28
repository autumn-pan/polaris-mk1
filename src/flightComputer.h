#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include "subsystems/control/sensors/sensors.h"
#include "subsystems/control/timeTracker.h"
#include "subsystems/io/pyro.h"
#include "subsystems/information/logger.h"
#include "subsystems/control/filter.h"


class FlightComputer
{
    public:
        // Process and measurement noise should be determined experimentally and hardcoded.
        // processNoise and measurementNoise are arrays of size 2, where:
        // [0] represents accelerometer noise 
        // [1] represents barometric altimeter noise
        // The kalman filter is the only subsystem that cannot be hardcoded into this library, as variances will vary.
        FlightComputer(float processNoise [2], float measurementNoise [2], float seaLevelPressure);
        void update();
        
    private:
        Logger * logger;
        TimeTracker * timeTracker;
        SensorStack * sensors;
        PyroChannel * pyro1; // Pyro channels to activate pyrotechnic devices
        PyroChannel * pyro2;
        KalmanFilter * filter;

        float seaLevelPressure;
};

#endif