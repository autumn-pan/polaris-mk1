#ifndef FILTER_H
#define FILTER_H
#include <eigen.h>

class KalmanFilter
{
    public:
        KalmanFilter(float processNoise = 1.0, float measurementNoise = 1.0);

        void update(float measuredAcceleration, float measuredPosition);
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
        float processNoise;
        float measurementNoise; 

};
#endif