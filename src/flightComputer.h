#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include "subsystems/control/sensors/sensors.h"
#include "subsystems/control/timing/timeTracker.h"
#include "subsystems/io/pyro.h"
#include "subsystems/information/logger.h"
#include "subsystems/control/filter.h"
#include "subsystems/control/stateDetection/stateDetector.h"
#include "subsystems/control/rotationHandler.h"
#include <eigen.h>

class FlightComputer
{
    public:
        // Process and measurement noise should be determined experimentally and hardcoded.
        // processNoise and measurementNoise are arrays of size 2, where:
        // [0] represents accelerometer noise 
        // [1] represents barometric altimeter noise
        // The kalman filter is the only subsystem that cannot be hardcoded into this library, as variances will vary.
        FlightComputer(float processNoise [2], float measurementNoise [2], float seaLevelPressure, float maxProcessNoise, float maxMeasurementNoise);
        void update(Eigen::Vector3f  control);
        
    private:
        Logger * logger;
        TimeTracker * timeTracker;
        SensorStack * sensors;
        PyroChannel * pyro1; // Pyro channels to activate pyrotechnic devices
        PyroChannel * pyro2;
        KalmanFilter * filter;
        StateDetector * stateDetector;
        RotationHandler * rotationHandler;

        // These are reasonable estimates for the maximum noise values from the IMUs.
        // This is useful for noise-proofing important systems such as apogee and launch detection.
        float maxProcessNoise;
        float maxMeasurementNoise;

        // 2 *(maxProcessNoise + maxMeasurementNoise)
        float cumulativeNoiseThreshold; // This is for validating that any measurements are from actual motion rather than sensor noise

        float seaLevelPressure;

        float stateVector[3]; 
        Quaternion* orientation;

        float xyVels[2];

        float mass;
};

#endif