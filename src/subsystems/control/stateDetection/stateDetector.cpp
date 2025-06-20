#include "stateDetector.h"
#include <cmath>

// Shifts the elements of an array left and inserts a new value on the right
float * arrayShift(float * array, float val, int arrayLen)
{
    // shift array elements
    for (int i = 1; i < arrayLen; i++)
    {
        array[i - 1] = array [i];
    }
    // insert new value
    array[arrayLen - 1] = val;

    return array;
}


// State Detector Constructor
StateDetector::StateDetector(float cumulativeNoiseThreshold)
    : cumulativeNoiseThreshold(cumulativeNoiseThreshold) {};

void StateDetector::update(float velocity)
{
    switch(state)
    {
        // Check for rocket launch
        case(GROUNDED):
            if(getLaunched())
                state = LAUNCHED;
            break;
        // Check for when the rocket descends
        case(LAUNCHED):
            if(getApogee())
                state = APOGEE;
            break;
        // Check for landing
        case(APOGEE):
            if(getLanded())
                state = LANDED;
            break;

        case(LANDED):
            break;
    }
}

bool StateDetector::getLaunched()
{
    for(int i = 0; i < VELOCITY_ARRAY_SIZE; i++)
    {
        if(velocities[i] < cumulativeNoiseThreshold)
            return false;
    }

    return true;
}

bool StateDetector::getApogee()
{
    for(int i = 0; i < VELOCITY_ARRAY_SIZE; i++)
    {
        if(velocities[i] < -cumulativeNoiseThreshold)
            return false;
    }

    return true;
}

bool StateDetector::getLanded()
{
    for(int i = 0; i < VELOCITY_ARRAY_SIZE; i++)
    {
        if(abs(velocities[i]) > cumulativeNoiseThreshold)
            return false;
    }

    return true;
}


