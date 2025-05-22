#include "sensors.h"
#include <BMI088.h>
#include <Wire.h>
#include <Arduino.h>

SensorStack::SensorStack() : accel(Wire, 0x18)
{
    Wire.begin();
    Wire.setClock(400000);
    accel.begin();
}