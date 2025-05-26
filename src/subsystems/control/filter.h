#ifndef FILTER_H
#define FILTER_H

#include <eigen.h>
#include "./timeTracker.h"
class KalmanFilter
{
    public:
        KalmanFilter(float processNoise = 1.0, float measurementNoise = 1.0, TimeTracker* timeTracker = nullptr);

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

        float processNoise; // TODO: split process and measurement noise into individual variables for acc and pos using an array
        float measurementNoise; 

        TimeTracker* timeTracker; // TimeTracker instance for determining dt dynamically

};
#endif