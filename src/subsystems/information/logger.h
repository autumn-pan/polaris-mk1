#ifndef LOGGER_H
#define LOGGER_H

#include <SD.h>
#include <SPI.h>

class Logger
{
    public:
        Logger(String notes = ""); // Constructor to initialize the SD card and create a log file
        void log(String data); // Writes data to the SD card and prints it to the serial monitor
        void logSensorData(); // Logs sensor data to the SD card
        void kill(); // Closes the log file
    private:
        const int chipSelect = BUILTIN_SDCARD;
        File dataFile;
        File eventFile;
};

#endif