#include "logger.h"
#include <SPI.h>
#include <SD.h>
#include "../control/sensors/sensors.h"

Logger::Logger(String notes)
{
    //Begin SD card
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD card initialization failed!");
        return;
    }
    Serial.println("SD card initialized successfully.");

    // Open or create the log directory
    if (!SD.exists("/logs"))
    {
        if (SD.mkdir("/logs"))
        {
            Serial.println("Log directory created successfully.");
        }
    }
    // Log files are enumerated in chronological order, i.2
    // log_0.txt, log_1.txt, etc.
    // Figure out the number of log files already present
    int logCount = 0;
    while (SD.exists(("/logs/log_" + String(logCount) + ".txt").c_str()))
    {
        logCount++;
    }

    // Create a new log file
    String name = "/logs/log_" + String(logCount) + ".txt";
    dataFile = SD.open(name.c_str(), FILE_WRITE);

    // Check if the file was opened successfully
    if (!dataFile)
    {
        Serial.println("Error opening log file!");
        return;
    }
    // Log the file creation (if successful)
    Serial.println("Log file created successfully.");


    // Write the header to the log file
    dataFile.println("POLARIS I FLIGHT LOG" + String(logCount) + "\n");
    dataFile.println(notes + "\n");
}

void Logger::log(String data)
{
    // Write data to the SD card
    if (dataFile)
    {
        dataFile.println(data);
    }
    else
    {
        Serial.println("Error writing to the log file");
        return;
    }

    // Print data to the serial monitor
    Serial.println(data);
}

void Logger::logSensorData()
{
    // Log sensor data to the SD card
    if (dataFile)
    { //Change these into meaningful information when other systems are implemented
        dataFile.print("Foo: ");
        dataFile.print("Bar");
    }
    else
    {
        Serial.println("Error writing to the log file");
        return;
    }
}

void Logger::kill()
{
    // Close the log file
    if (dataFile)
    {
        dataFile.close();
        Serial.println("Log file closed successfully.");
    }
    else
    {
        Serial.println("Data file not open");
        return;
    }
}

