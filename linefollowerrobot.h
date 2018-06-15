#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include <Arduino.h>

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

private:
    MotorDriver* m_motorDriver;
    LineSensor* m_lineSensor;
    FuzzyController* m_controller;

    float m_input;
    float m_output;
    int m_linearSpeed;
};

#endif // LINEFOLLOWERROBOT_H
