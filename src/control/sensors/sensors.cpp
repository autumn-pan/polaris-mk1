#include "sensors.h"
#include <BMI088.h>
#include <Wire.h>
#include <Arduino.h>

SensorStack::SensorStack() : accel(Wire, 0x18), gyro(Wire, 0x68)
{
    Wire.begin();
    Wire.setClock(400000);
    accel.begin();
}

// Getter functions for accelerometer and gyroscope data
float SensorStack::getAccelX() {return accel.getAccelX_mss();}
float SensorStack::getAccelY() {return accel.getAccelY_mss();}
float SensorStack::getAccelZ() {return accel.getAccelZ_mss();}
float SensorStack::getGyroX() {return gyro.getGyroX_rads();}
float SensorStack::getGyroY() {return gyro.getGyroY_rads();}
float SensorStack::getGyroZ() {return gyro.getGyroZ_rads();}

// Reads the sensor data; must be run every cycle
void SensorStack::updateSensorData()
{
    accel.readSensor();
    gyro.readSensor();
}