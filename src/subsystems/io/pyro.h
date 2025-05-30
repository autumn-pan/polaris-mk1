#ifndef PYRO_H
#define PYRO_H

#include "../information/logger.h"

// Pyrotechnic Channels
enum PYRO_PINS
{
    PYRO_PIN1 = 0,
    PYRO_PIN2 = 1,
    PYRO_PIN3 = 2,
};

// Pyrotechnic Channel Class
class PyroChannel
{
    public:
        PyroChannel(int pin, unsigned int duration, Logger * logger);
        void fire(); // Send a signal out to the pyro channel for the duration
        void reset();
        bool isFired(); 
        bool update(); // Ensures that the pyro channel is stopped correctly; to be run every cycle
        bool isFiring(); // Returns true if the pyro channel is currently firing
        
    private:
        int pin;
        unsigned int duration;
        unsigned long fireTime;
        bool fired;
        bool active;

        Logger * logger; // Logger for logging pyro events
};

#endif