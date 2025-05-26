#ifndef TIME_TRACKER_H
#define TIME_TRACKER_H
#include <Arduino.h>

class TimeTracker
{
    public:
        TimeTracker();
        void update();
        void start();
        unsigned int getElapsedTime();
        unsigned int getTime();
        unsigned int getTimeStep();
        
    private:
        unsigned int time;
        unsigned int startTime;
        unsigned int elapsedTime;
        unsigned int lastUpdateTime;
        unsigned int dt;
        bool running;
};

#endif