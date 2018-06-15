#include "linefollowerrobot.h"
#include "linesensor.h"
#include "motordriver.h"

LineFollowerRobot::LineFollowerRobot()
{
}

void LineFollowerRobot::init()
{
    m_motorDriver = new MotorDriver();
    m_lineSensor = new LineSensor();
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorDriver->setSpeed(speed, speed);
}

void LineFollowerRobot::readSensors()
{
    m_lineSensor->read();
}
