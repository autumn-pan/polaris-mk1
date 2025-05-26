#include "sensors.h"
#include <BMI088.h>
#include <Wire.h>
#include <Arduino.h>
#include "../../information/logger.h"

SensorStack::SensorStack(Logger * logger) : accel(Wire, 0x18), gyro(Wire, 0x68)
{
    //First, initialize the logger
    this->logger = logger;
    // Set up I2C communication
    Wire.begin();
    Wire.setClock(400000);
    // Initialize and log the status of the sensors
    
    // Accelerometer
    if(accel.begin())
        logger->log("Accelerometer initialized successfully");
    else
        logger->log("Accelermeter initialization failed");

    // Gyroscope
    if (gyro.begin())
        logger->log("Gyroscope initialized successfully");
    else
        logger->log("Gyroscope initialization failed");

    // Barometer
    if(bmp.begin_I2C(0x76, &Wire))
        logger->log("Barometer initialized successfully");
    else
        logger->log("Barometer initialization failed");
}

// Getter functions for accelerometer and gyroscope data
float SensorStack::getAccelX() { return accel.getAccelX_mss(); }
float SensorStack::getAccelY() { return accel.getAccelY_mss(); }
float SensorStack::getAccelZ() { return accel.getAccelZ_mss(); }
float SensorStack::getGyroX() { return gyro.getGyroX_rads(); }
float SensorStack::getGyroY() { return gyro.getGyroY_rads(); }
float SensorStack::getGyroZ() { return gyro.getGyroZ_rads(); }

// Getter functions for pressure and altitude
float SensorStack::getPressure() { return bmp.readPressure(); }
float SensorStack::getAltitude(float seaLevel) { return bmp.readAltitude(seaLevel);} 


// Reads the sensor data; must be run every cycle
void SensorStack::updateSensorData()
{
    accel.readSensor();
    gyro.readSensor();
    bmp.performReading();

    // Store the sensor data
    accelX = getAccelX();
    accelY = getAccelY();
    accelZ = getAccelZ();
    gyroX = getGyroX();
    gyroY = getGyroY();
    gyroZ = getGyroZ();
    pressure = getPressure();
    altitude = getAltitude(SEA_LEVEL_PRESSURE);
}