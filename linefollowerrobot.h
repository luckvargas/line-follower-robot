#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include "util/util.h"
#include <Arduino.h>
#include <LED.h>

class Button;
class LineSensor;
class MotorDriver;
class FuzzyController;

class LineFollowerRobot {
public:
    LineFollowerRobot();

    void init();
    void moveForward(const uint32_t& speed);
    void readSensors();
    void follow();

    void setLinearSpeed(int linearSpeed);

    void calibrate();

private:
    MotorDriver* m_motorDriver;
    LineSensor* m_lineSensor;
    FuzzyController* m_controller;
    Button* m_startButton;
    LED* m_led;
    ElapsedTimer m_timer;

    float m_input;
    float m_output;
    int m_linearSpeed;

    const uint8_t startButtonPin = 12;
    const uint8_t indicatorLedPin = 13;
};

#endif // LINEFOLLOWERROBOT_H
