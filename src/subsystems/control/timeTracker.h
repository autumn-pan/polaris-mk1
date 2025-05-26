#ifndef TIME_TRACKER_H
#define TIME_TRACKER_H
#include <Arduino.h>

class TimeTracker
{
    public:
        TimeTracker();
        void update();
        void start();
        // Getter functions: simply returns the stored time values
        unsigned int getElapsedTime();
        unsigned int getTime();
        unsigned int getTimeStep();

    private:
        unsigned int time; // Time since boot
        unsigned int startTime; // Time of launch
        unsigned int elapsedTime; // Time since launch
        unsigned int lastUpdateTime; // The time of the previous cycle, useful for derivatives and stuff
        unsigned int dt; // The length of a time step; the change in time between cycles
        bool running; // whether or not the rocket has launched
};

#endif