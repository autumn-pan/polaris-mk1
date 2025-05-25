#include "sd.h"
#include <SPI.h>
#include <SD.h>
#include "../control/sensors/sensors.h"

SDCard::SDCard()
{
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD card initialization failed!");
        return;
    }
    //create a file to log data
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (!dataFile)
    {
        Serial.println("Error opening data.txt");
        return;
    }

    dataFile.println("POLARIS I");
    Serial.println("SD card initialized.");
}

// run every couple cycles to log data, preferably only a few times per second
void SDCard::log()
{
    if (!dataFile)
    {
        Serial.println("Error opening data.txt");
        return;
    }
    // Write sensor data to the file
    dataFile.print("Hello, World!"); // TODO: replace with actual sensor data
}