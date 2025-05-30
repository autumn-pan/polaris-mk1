#ifndef SENSORS_H
#define SENSORS_H

// Change this to the precise sea level pressure for your location
#define SEA_LEVEL_PRESSURE 1013.25 // hPa


#include <BMI088.h>
#include <Adafruit_BMP3XX.h>
#include <Wire.h>
#include <Arduino.h>
#include "../../information/logger.h"

class SensorStack
{
    public:
        SensorStack(Logger * logger);

        void updateSensorData();
        float getAccelX();
        float getAccelY();
        float getAccelZ();
        float getGyroX();
        float getGyroY();
        float getGyroZ();

        float getPressure();
        float getAltitude(float seaLevel);

    private:
        Bmi088Accel accel;
        Bmi088Gyro gyro;
        Adafruit_BMP3XX bmp;

        // Logger
        Logger * logger;
        // Stored sensor data
        float accelX, accelY, accelZ;
        float gyroX, gyroY, gyroZ;
        float pressure, altitude;
        
    };
#endif