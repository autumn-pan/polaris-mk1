#include <eigen.h>
#include "filter.h"
#include <Arduino.h>
#include <cmath>
#include "./sensors/sensors.h"
#include "./timeTracker.h"

KalmanFilter::KalmanFilter(float processNoise[], float measurementNoise[], TimeTracker * timeTracker)
{
    // Initialize state vector; estimated initial values
    x << 0, 0, 0;    
    // Initialize covariance matrices
    P = Eigen::Matrix3f::Identity();
    Q  <<
        processNoise[0], 0, 0,
        0, 0, 0,
        0, 0, processNoise[1]; // Process noise covariance matrix Q

    R <<
        measurementNoise[0], 0, 0,
        0, 1e6, 0,
        0, 0, measurementNoise[1]; // Measurement noise covariance matrix R
    
    // Initialize Kalman gain and identity matrix
    K = Eigen::Matrix3f::Zero();
    I = Eigen::Matrix3f::Identity();
    
}

void KalmanFilter::update(float measuredAcceleration, float measuredPosition)
{
    dt = timeTracker->getTimeStep() / 1000.0f; // Convert milliseconds to seconds

    // State transition matrix (assuming constant acceleration model)
    F << 1, 0, 0, // State transition for acceleration
         dt, 1, 0, // State transition for velocity
         0.5 * dt * dt, dt, 1; // State transition for position
    // Predict the next state...
    xp = F * x; // no control matrix... yet

    P = F * P * F.transpose() + Q; // Update estimate error covariance
    // Measurement vector
    Eigen::Vector3f z;
    z << measuredAcceleration, 0, measuredPosition; // Assuming acceleration is the first measurement and position is the third
    // Measurement matrix (assuming we measure acceleration and position)

    Eigen::Matrix<float, 3, 3> H;
    H << 1, 0, 0, // Measure acceleration
         0, 0, 0,
         0, 0, 1; // Measure position

    // Calculate Kalman gain
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
    // Update state estimate
    x = xp + K * (z - H * xp);
    // Update estimate error covariance
    P = (I - K * H) * P;    
}

float KalmanFilter::getAcceleration()
{
    return x(0); // Return estimated acceleration
}
float KalmanFilter::getVelocity()
{

    return x(1); // Return estimated velocity
}
float KalmanFilter::getPosition()
{
    return x(2); // Return estimated position
}