#ifndef SENSORS_H
#define SENSORS_H
#include <BMI088.h>
#include <Wire.h>
#include <Arduino.h>

class SensorStack
{
    public:
        SensorStack();

        void readSensors();
        float getAccelX();
        float getAccelY();
        float getAccelZ();
        float getGyroX();
        float getGyroY();
        float getGyroZ();
    private:
        Bmi088Accel accel;

        float accelX, accelY, accelZ;
        float gyroX, gyroY, gyroZ;
    };
#endif