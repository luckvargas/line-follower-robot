#include "linefollowerrobot.h"
#include "fuzzycontroller.h"
#include "linesensor.h"
#include "motordriver.h"
#include <Button.h>

LineFollowerRobot::LineFollowerRobot()
    : m_lastEncoderRead(0, 0)
{
}

void LineFollowerRobot::calibrate()
{
    uint32_t calibrationSpeed = 1000;
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

void LineFollowerRobot::waitButtonPress()
{
    Serial << "Waiting for button press..." << endl;
    while (!m_startButton->isPressed()) {
        m_led->blink(100);
    }
    delay(1000);
}

void LineFollowerRobot::init()
{
    m_motorDriver = new MotorDriver();
    m_lineSensor = new LineSensor();
    m_controller = new FuzzyController();
    m_startButton = new Button(startButtonPin, PULLUP);
    m_led = new LED(indicatorLedPin);

    waitButtonPress();

    Serial << "Start calibration..." << endl;
    calibrate();
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorDriver->setSpeed(speed, speed);
}

void LineFollowerRobot::readLine()
{
    m_lineSensor->read();
}

void LineFollowerRobot::readOdometry()
{
    Pair<uint32_t, uint32_t> encoderRead = m_motorDriver->getEncoders();

    uint32_t deltaLeftDistance = (encoderRead.first() - m_lastEncoderRead.first()) / countsPerCentimeter;
    uint32_t deltaRightDistance = (encoderRead.second() - m_lastEncoderRead.second()) / countsPerCentimeter;

    uint32_t distance = (deltaLeftDistance + deltaRightDistance) / 2.0;

    // Update robot position
    m_lastPosition.y += distance * cos(m_lastPosition.theta);
    m_lastPosition.x += distance * sin(m_lastPosition.theta);
    m_lastPosition.theta += (deltaLeftDistance - deltaRightDistance) / distanceBetweenWheels;
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
