#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include "util/util.h"
#include <Arduino.h>
#include <LED.h>

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

class LineFollowerRobot {
public:
    LineFollowerRobot();

    void init();

    void moveForward(const uint32_t& speed);

    void readLine();

    void readOdometry();

    void follow();

    void setLinearSpeed(int linearSpeed);

    void calibrate();

private:
    void waitButtonPress();

    MotorDriver* m_motorDriver;
    LineSensor* m_lineSensor;
    FuzzyController* m_controller;
    Button* m_startButton;
    LED* m_led;
    ElapsedTimer m_timer;

    float m_input;
    float m_output;
    int m_linearSpeed;

    Position m_lastPosition;
    Pair<uint32_t, uint32_t> m_lastEncoderRead;

    const uint8_t startButtonPin = 12;
    const uint8_t indicatorLedPin = 13;
    const float distanceBetweenWheels = 100.0; // Distance between wheels - 10cm
    const float countsPerCentimeter = 100.0;
};
#endif // LINEFOLLOWERROBOT_H
