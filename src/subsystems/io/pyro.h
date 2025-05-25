// Pyrotechnic Channels
enum PYRO_PINS
{
    PYRO_PIN1 = 0,
    PYRO_PIN2 = 1,
    PYRO_PIN3 = 2,
};

// Pyrotechnic Channel Class
class PyroChannel
{
    public:
        PyroChannel(int pin, unsigned int duration);
        void fire();
        void reset();
        bool isFired();
        bool update();
    private:
        int pin;
        unsigned int duration;
        unsigned long fireTime;
        bool fired;
        bool active;
};