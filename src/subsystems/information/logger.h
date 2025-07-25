#ifndef LOGGER_H
#define LOGGER_H

#include <SD.h>
#include <SPI.h>
#include "../control/timing/timeTracker.h"

class Logger
{
    public:
        Logger(TimeTracker * timeTracker);  // Constructor to initialize the SD card and create a log file
        void log(String data); // Writes data to the SD card and prints it to the serial monitor
        void logSensorData(float data[6]); // Logs sensor data to the SD card
        void beginLine();
        void kill(); // Closes the log file

        void logDataTriple(float data[3]);
        
    private:
        const int chipSelect = BUILTIN_SDCARD;
        File dataFile;
        File eventFile;
        TimeTracker * timeTracker;
};

#endif