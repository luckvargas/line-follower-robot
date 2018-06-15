#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include <Arduino.h>

class LineSensor;
class MotorDriver;

class LineFollowerRobot {
public:
    LineFollowerRobot();

    void init();
    void moveForward(const uint32_t& speed);
    void readSensors();

private:
    MotorDriver* m_motorDriver;
    LineSensor* m_lineSensor;
};

#endif // LINEFOLLOWERROBOT_H
