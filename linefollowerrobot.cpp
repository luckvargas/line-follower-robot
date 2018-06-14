#include "linefollowerrobot.h"

LineFollowerRobot::LineFollowerRobot()
{
}

void LineFollowerRobot::init()
{
    m_motorController = new MotorController();
    m_lineSensor = new LineSensor();
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorController->setSpeed(speed, speed);
}

void LineFollowerRobot::readSensors()
{
    m_lineSensor->read();
}
