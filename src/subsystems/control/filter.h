#ifndef FILTER_H
#define FILTER_H

#include <eigen.h>
#include "./timeTracker.h"
class KalmanFilter
{
    public:
        // Process and measurement noise should be determined experimentally and hardcoded.
        // processNoise and measurementNoise are arrays of size 2, where:
        // [0] represents accelerometer noise 
        // [1] represents barometric altimeter noise
        KalmanFilter(float processNoise [2], float measurementNoise [2], TimeTracker* timeTracker = nullptr);

        void update(float measuredAcceleration, float measuredPosition); // Update the filter with new measurements; run every cycle

        // Getters for the state variables
        float getAcceleration(); 
        float getVelocity();
        float getPosition();

    private:
        // State vector: x = [acceleration, velocity, position]
        Eigen::Vector3f x; // State vector
        Eigen::Vector3f xp; // Predicted state vector
        Eigen::Matrix3f P; // Estimate error covariance matrix
        Eigen::Matrix3f Q; // Process noise covariance matrix
        Eigen::Matrix3f R; // Measurement noise covariance matrix
        Eigen::Matrix3f K; // Kalman gain
        Eigen::Matrix3f I; // Identity matrix
        Eigen::Matrix3f F; // State transition matrix

        float dt; // Time step
        // Note: while the time variable usually stores milliseconds, seconds are used in the kalman filter

        float processNoise [2];
        float measurementNoise [2]; 

        TimeTracker* timeTracker; // TimeTracker instance for determining dt dynamically

};
#endif