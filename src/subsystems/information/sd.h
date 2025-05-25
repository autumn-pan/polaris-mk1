#include <SD.h>
#include <SPI.h>

class SDCard
{
    public:
        SDCard();
        void log();
    private:
        const int chipSelect = BUILTIN_SDCARD;
        File dataFile;
};