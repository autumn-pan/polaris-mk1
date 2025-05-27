#include "timeTracker.h"
#include <Arduino.h>

TimeTracker::TimeTracker()
{
    time = millis();
    lastUpdateTime = 0;
    running = false;
}

void TimeTracker::update()
{
    time = millis();
    // If the time has not changed, do nothing
    if (time == lastUpdateTime)
    {
        return;
    }
    
    //update dt
    dt = time - lastUpdateTime;
    lastUpdateTime = time;
        
    // if the rocket has launched, update the elapsed time
    if (running)
    {
        //update time since launch
        elapsedTime = time - startTime;
    }
}

void TimeTracker::start()
{
    startTime = millis();
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