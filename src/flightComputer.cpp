#include "flightComputer.h"
#include "subsystems/control/filter.h"
#include "subsystems/control/timeTracker.h"
#include "subsystems/control/sensors/sensors.h"
#include "subsystems/information/logger.h"
#include "subsystems/io/pyro.h"
#include "pins.h"
#include <Arduino.h>

// ts pmo ong icl frfr
FlightComputer::FlightComputer(float processNoise[2], float measurementNoise[2])
{
    // instantiate all flight components
    timeTracker = new TimeTracker();
    // data logging
    logger = new Logger();
    // control instances
    sensors = new SensorStack(logger);
    filter = new KalmanFilter(processNoise, measurementNoise, timeTracker);
    // pyro channels

    pyro1 = new PyroChannel(12, 1000, logger); // 12 is a placeholder pin value
    pyro2 = new PyroChannel(13, 1000, logger); // 13 is a placeholder pin value


    // finish initialization
    
}