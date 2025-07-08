#include "flightComputer.h"
#include "subsystems/control/filter.h"
#include "subsystems/control/timing/timeTracker.h"
#include "subsystems/control/sensors/sensors.h"
#include "subsystems/information/logger.h"
#include "subsystems/io/pyro.h"
#include <Arduino.h>

FlightComputer::FlightComputer(float processNoise[2], float measurementNoise[2], float seaLevelPressure, float maxProcessNoise, float maxMeasurementNoise)
{
    // instantiate all flight components
    timeTracker = new TimeTracker();

    // data logging
    logger = new Logger(timeTracker);

    // control instances
    sensors = new SensorStack(logger);
    filter = new KalmanFilter(processNoise, measurementNoise, timeTracker);

    // pyro channels 
    pyro1 = new PyroChannel(12, 1000, logger); // 12 is a placeholder pin value
    pyro2 = new PyroChannel(13, 1000, logger); // 13 is a placeholder pin value

    stateDetector = new StateDetector(cumulativeNoiseThreshold);

    this->seaLevelPressure = seaLevelPressure;

    // Set up noise maxima
    this->maxMeasurementNoise = maxMeasurementNoise;
    this->maxProcessNoise = maxProcessNoise;

    this->cumulativeNoiseThreshold = 2 * (maxMeasurementNoise + maxProcessNoise);


}



void FlightComputer::update()
{
    // keep track of time
    timeTracker->update();

    // The rocket's state is also important to track
    stateDetector->update(stateVector[1]);

    // Update pyro channels if they're active
    if(pyro1->isFiring())
        pyro1->update();

    if(pyro2->isFiring())
        pyro2->update();

    // Update state information
    sensors->updateSensorData();
    filter->update(sensors->getAccelY(), sensors->getAltitude(seaLevelPressure));
}
