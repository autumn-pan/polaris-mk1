#ifndef STATE_DETECTOR
#define STATE_DETECTOR

const int VELOCITY_ARRAY_SIZE = 5;

enum State {
    GROUNDED,
    LAUNCHED,
    APOGEE,
    LANDED
};

class StateDetector
{
    public:
        StateDetector(float culumativeNoiseThreshold);

        void update(float velocity);

        void checkLaunch();
        void checkApogee();
        void checkLanded();

        bool getLaunched();
        bool getApogee();
        bool getLanded();

    private:
        float cumulativeNoiseThreshold;

        float velocities[VELOCITY_ARRAY_SIZE] = {0};

        State state;
};


#endif