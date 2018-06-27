#include "linefollowerrobot.h"
#include "fuzzycontroller.h"
#include "linesensor.h"
#include "motordriver.h"
#include <Button.h>

#define TWOPI (2 * PI)

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
    }
    delay(1000);
}

void LineFollowerRobot::init()
{
    m_motorDriver = new MotorDriver();
    m_lineSensor = new LineSensor();
    m_controller = new FuzzyController();
    m_startButton = new Button(startButtonPin, PULLUP);
    //    m_led = new LED(indicatorLedPin);
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorDriver->setSpeed(speed, speed);
}

void LineFollowerRobot::readLine()
{
    m_lineSensor->read(false);
}

void LineFollowerRobot::readOdometry()
{
    Pair<uint32_t, uint32_t> encoderRead = m_motorDriver->getEncoders();

    float deltaLeftDistance = (encoderRead.first() - m_lastEncoderRead.first()) / countsPerCentimeter;
    float deltaRightDistance = (encoderRead.second() - m_lastEncoderRead.second()) / countsPerCentimeter;

    // Update robot position
    float distance = (deltaLeftDistance + deltaRightDistance) / 2.0;
    m_lastPosition.y += distance * cos(m_lastPosition.theta);
    m_lastPosition.x += distance * sin(m_lastPosition.theta);
    m_lastPosition.theta += (deltaLeftDistance - deltaRightDistance) / distanceBetweenWheels;

    // Theta between 0 and 2*PI
    m_lastPosition.theta -= (float)((int)(m_lastPosition.theta / TWOPI)) * TWOPI;
    if (m_lastPosition.theta < -PI) {
        m_lastPosition.theta += TWOPI;
    } else if (m_lastPosition.theta > PI) {
        m_lastPosition.theta -= TWOPI;
    }

    Serial << "X = " << m_lastPosition.x << "\t Y = " << m_lastPosition.y << " THETA = " << m_lastPosition.theta << endl;
}

void LineFollowerRobot::scan()
{
    m_lastPosition = Position();

    do {
        follow(scanSpeed);
        readOdometry();

        // Segment LaneSegment(length, radius);
        // m_lane.push_back(newSegment);
    } while (closeToOrigin());
    stop();
}

bool LineFollowerRobot::closeToOrigin()
{
    //TODO: Check if position is close to origin
    return false;
}

void LineFollowerRobot::follow()
{
    this->follow(m_linearSpeed);
}

void LineFollowerRobot::follow(float speed)
{
    m_input = m_lineSensor->read(false);
    m_output = m_controller->evaluate(m_input);

    m_motorDriver->setSpeed(speed + m_output, m_linearSpeed - m_output);
}

void LineFollowerRobot::stop()
{
    m_motorDriver->setSpeed(0, 0);
}

void LineFollowerRobot::setLinearSpeed(float linearSpeed)
{
    m_linearSpeed = linearSpeed;
}
