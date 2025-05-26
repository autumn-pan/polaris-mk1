#include <Arduino.h>
#include "pyro.h"

#include "../information/logger.h"

PyroChannel::PyroChannel(int pin, unsigned int duration, Logger * logger)
{
    this->pin = pin;
    this->duration = duration;
    this->fired = false;
    this->logger = logger;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}


// initializes the firing sequence
void PyroChannel::fire()
{
    if (!fired)
    {
        fired = true;
        active = true;
        fireTime = millis();
        digitalWrite(pin, HIGH);
    }
}

// Ensures that the pyro channel is stopped correctly; to be run every cycle
bool PyroChannel::update()
{
    if (active)
    {
        if (millis() - fireTime < duration)
        {
            return true;
        }
        else
        {
            active = false;
            digitalWrite(pin, LOW);
        }
    }
    return false;
}

void PyroChannel::reset()
{
    if (active)
    {
        logger->log("Cannot reset when pyro channel is active.");
        return;
    }

    fired = false;
    return;
}