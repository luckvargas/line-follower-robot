#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include "util/util.h"
#include <Arduino.h>
#include <LED.h>

#ifdef __AVR__
#include <StandardCplusplus.h>
#endif
#include <vector>

class Button;
class LineSensor;
class MotorDriver;
class FuzzyController;

struct Position {
    Position() {}

    Position(float x, float y, float theta)
    {
        this->x = x;
        this->y = y;
        this->theta = theta;
    }

    float x, y, theta = 0;
};

struct LaneSegment {
    LaneSegment() {}

    LaneSegment(float length, float radius)
    {
        this->length = length;
        this->radius = radius;
    }

    float length;
    float radius;
};

class LineFollowerRobot {
public:
    LineFollowerRobot();

    void init();

    void moveForward(const uint32_t& speed);

    void readLine();

    void readOdometry();

    void scan();

    void follow();

    void follow(float speed);

    void setLinearSpeed(float linearSpeed);

    void calibrate();

    void waitButtonPress();

    void stop();

private:
    bool closeToOrigin();

    ///< Periferics
    MotorDriver* m_motorDriver;
    LineSensor* m_lineSensor;
    FuzzyController* m_controller;
    Button* m_startButton;
    ElapsedTimer m_timer;

    ///< Control variables
    float m_input;
    float m_output;

    ///< Speed parameters
    int m_maxSpeed;
    float m_linearSpeed;

    ///< Odometry and Mapping
    std::vector<LaneSegment> m_lane;
    Position m_lastPosition;
    Pair<uint32_t, uint32_t> m_lastEncoderRead;

    ///< Constraints
    const uint8_t startButtonPin = 12;
    const uint8_t indicatorLedPin = 13;
    const float distanceBetweenWheels = 100.0; // Distance between wheels - 10cm
    const float countsPerCentimeter = 100.0;
    const float scanSpeed = 1000.0;
};
#endif // LINEFOLLOWERROBOT_H
