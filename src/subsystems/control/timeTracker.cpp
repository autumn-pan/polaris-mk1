#include "timeTracker.h"
#include <Arduino.h>

TimeTracker::TimeTracker()
{
    time = 0;
    running = false;
}

void TimeTracker::update()
{
    time = millis();

    // if the rocket has launched, update the elapsed time
    if (running)
    {
        //update time since launch
        elapsedTime = time - startTime;
        //update dt
        dt = time - lastUpdateTime;
        lastUpdateTime = time;
    }
}

void TimeTracker::start()
{
    startTime = millis();
    lastUpdateTime = startTime;
    elapsedTime = 0;
    running = true;
}

unsigned int TimeTracker::getElapsedTime()
{
    return elapsedTime;
}

unsigned int TimeTracker::getTime()
{
    return time;
}

unsigned int TimeTracker::getTimeStep()
{
    return dt;
}