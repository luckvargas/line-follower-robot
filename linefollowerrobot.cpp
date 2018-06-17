#include "linefollowerrobot.h"
#include "fuzzycontroller.h"
#include "linesensor.h"
#include "motordriver.h"
#include <Button.h>

LineFollowerRobot::LineFollowerRobot()
    : m_startButton(new Button(startButtonPin, PULLUP))
{
}

void LineFollowerRobot::calibrate()
{
    uint32_t calibrationSpeed = 30;
    long calibrationTime = 2000;

    // Rotate robot and calibrate
    m_motorDriver->setSpeed(calibrationSpeed, -calibrationSpeed);
    m_timer.start();
    while (m_timer.elapsed() < calibrationTime) {
        m_lineSensor->calibrate();
    }

    // Rotate robot to other direction
    m_motorDriver->setSpeed(-calibrationSpeed, calibrationSpeed);
    m_timer.start();
    while (m_timer.elapsed() < calibrationTime) {
        m_lineSensor->calibrate();
    }
}

void LineFollowerRobot::init()
{
    m_motorDriver = new MotorDriver();
    m_lineSensor = new LineSensor();
    m_controller = new FuzzyController();

    while (!m_startButton->isPressed()) {
        delay(100);
    }

    calibrate();
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorDriver->setSpeed(speed, speed);
}

void LineFollowerRobot::readSensors()
{
    m_lineSensor->read();
}

void LineFollowerRobot::follow()
{
    m_input = m_lineSensor->read();
    m_output = m_controller->evaluate(m_input);

    m_motorDriver->setSpeed(m_linearSpeed + m_output, m_linearSpeed - m_output);
}

void LineFollowerRobot::setLinearSpeed(int linearSpeed)
{
    m_linearSpeed = linearSpeed;
}
