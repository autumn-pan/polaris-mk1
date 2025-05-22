#ifndef SENSORS_H
#define SENSORS_H
#include <BMI088.h>
#include <Adafruit_BMP3XX.h>
#include <Wire.h>
#include <Arduino.h>

class SensorStack
{
    public:
        SensorStack();

        void updateSensorData();
        float getAccelX();
        float getAccelY();
        float getAccelZ();
        float getGyroX();
        float getGyroY();
        float getGyroZ();

    private:
        Bmi088Accel accel;
        Bmi088Gyro gyro;
        Adafruit_BMP3XX bmp;
        float accelX, accelY, accelZ;
        float gyroX, gyroY, gyroZ;
    };
#endif