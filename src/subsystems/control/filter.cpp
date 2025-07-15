#include <eigen.h>
#include "filter.h"
#include <Arduino.h>
#include <cmath>
#include "./sensors/sensors.h"
#include "./timing/timeTracker.h"

KalmanFilter::KalmanFilter(float processNoise[], float measurementNoise[], TimeTracker* timeTracker)
{
    // First, initialize the time tracker
    this->timeTracker = timeTracker;

    // Initialize state vector; estimated initial values
    x = Eigen::Vector3f::Zero(); // [acceleration, velocity, position]
    
    // Initialize covariance matrices
    P = Eigen::Matrix3f::Identity();
    Q  <<
        processNoise[0], 0, 0,
        0, 0, 0,
        0, 0, processNoise[1]; // Process noise covariance matrix Q

    R <<
        measurementNoise[0], 0, 0,
        0, 0, 0,
        0, 0, measurementNoise[1]; // Measurement noise covariance matrix R
    // The control vector should go (accX, accY, accZ, and accZ is the only one I really care about. See massTracker for thrust=to-acc conversion)
    B <<
        0, 0, 1,
        0, 0, dt,
        0, 0, 0.5*dt*dt;

    // Initialize Kalman gain and identity matrix
    K = Eigen::Matrix3f::Zero();
    I = Eigen::Matrix3f::Identity();
    

    processNoise = processNoise;
    measurementNoise = measurementNoise;
}

void KalmanFilter::update(float measuredAcceleration, float measuredPosition, Eigen::Vector3f control)
{
    // Before anything, update dt based on the timeTracker
    dt = timeTracker->getTimeStep() / 1000.0f;
    
    // State transition matrix (assuming constant acceleration model)
    F << 1, 0, 0, // State transition for acceleration
         dt, 1, 0, // State transition for velocity
         0.5 * dt * dt, dt, 1; // State transition for position

    // Predict the next state...
    xp = F * x + B*control;
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
std::array<float, 3> KalmanFilter::getState()
{
    return {x(0), x(1), x(2)};
}