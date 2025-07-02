#include "logger.h"
#include <SPI.h>
#include <SD.h>
#include "../control/sensors/sensors.h"

Logger::Logger(String notes) // notes are arbitrary. remove.
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
    // Create a new event log file
    String eventName = "/logs/eventLogs_" + String(logCount) + ".txt";
    eventFile = SD.open(eventName.c_str(), FILE_WRITE);

    // Check if the file was opened successfully
    if (!eventFile)
    {
        Serial.println("Error opening event log file!");
        return;
    }

    // Log the file creation (if successful)
    Serial.println("Event Log file created successfully.");

    // Write event log header
    eventFile.println("Polaris I Flight Event Log " + String(logCount));

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
    dataFile.println("foo, bar, baz"); //replace these with meaningful sensor info
}

void Logger::log(String data)
{
    // Write data to the SD card
    if (eventFile)
    {
        eventFile.println(data);
    }
    else
    {
        Serial.println("Error writing to the event log file");
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
        dataFile.print("foo, ");
        dataFile.print("bar, ");
        dataFile.print("baz");
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

