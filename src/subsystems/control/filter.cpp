#include <eigen.h>
#include "filter.h"
#include <Arduino.h>
#include <cmath>
#include "./sensors/sensors.h"
#include "./timeTracker.h"

KalmanFilter::KalmanFilter(float processNoise, float measurementNoise, TimeTracker* timeTracker)
{
    // First, initialize the time tracker
    this->timeTracker = timeTracker;

    // Then, initialize dt
    dt = timeTracker->getTimeStep()/1000.0f; // Convert milliseconds to seconds

    // Initialize state vector; estimated initial values
    x = Eigen::Vector3f::Zero(); // [acceleration, velocity, position]
    
    // Initialize covariance matrices
    P = Eigen::Matrix3f::Identity();
    Q = Eigen::Matrix3f::Identity() * processNoise; // Process noise covariance
    R = Eigen::Matrix3f::Identity() * measurementNoise; // Measurement noise covariance
    
    // Initialize Kalman gain and identity matrix
    K = Eigen::Matrix3f::Zero();
    I = Eigen::Matrix3f::Identity();
    
    // State transition matrix (assuming constant acceleration model)
    F << 1, dt, 0.5*dt * dt,
         0, 1, dt,
         0, 0, 1;

    this->processNoise = processNoise;
    this->measurementNoise = measurementNoise;
}

void KalmanFilter::update(float measuredAcceleration, float measuredPosition)
{
    // Before anything, update dt based on the timeTracker
    dt = timeTracker->getTimeStep() / 1000.0f;
    
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