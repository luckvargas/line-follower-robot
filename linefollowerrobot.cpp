#include "linefollowerrobot.h"
#include "PID_v1.h"
#include "config.h"
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
    uint32_t calibrationSpeed = 500;
    long calibrationTime = 1500;

    Serial << "CALIBRANDO!!!" << endl;
    // Rotate robot and calibrate
    m_motorDriver->setSpeed(calibrationSpeed, -calibrationSpeed);
    m_timer.start();
    while (m_timer.elapsed() < calibrationTime) {
        m_lineSensor->calibrate();
    }

    // Rotate robot to10 other direction
    m_motorDriver->setSpeed(-calibrationSpeed, calibrationSpeed);
    m_timer.start();
    while (m_timer.elapsed() < calibrationTime) {
        m_lineSensor->calibrate();
    }
    m_motorDriver->setSpeed(0, 0);

    m_calibrated = true;
    Serial << "CALIBROU!" << endl;
}

void LineFollowerRobot::waitButtonPress()
{
    Serial << "Waiting for button press... " << endl;
    while (digitalRead(startButtonPin)) {
        digitalWrite(indicatorLedPin, LOW);
        delay(100);
        digitalWrite(indicatorLedPin, HIGH);
        delay(100);
        // Serial << "APERTA PORRA: " << digitalRead(startButtonPin) << endl;
    }
    Serial << "APERTOU!!!" << endl;
    delay(2000);
}

void LineFollowerRobot::init()
{
    m_motorDriver = new MotorDriver();
    m_lineSensor = new LineSensor();
    m_fuzzyController = new FuzzyController();
    pinMode(startButtonPin, INPUT_PULLUP);
    pinMode(indicatorLedPin, OUTPUT);
    digitalWrite(indicatorLedPin, LOW);

    m_pidController = new PID(&m_input, &m_output, &m_setpoint, m_kp, m_ki, m_kd, DIRECT);
    m_pidController->SetSampleTime(3);
    m_pidController->SetMode(AUTOMATIC);
    m_motorDriver->setSpeed(0, 0);
}

void LineFollowerRobot::updatePid()
{
    m_pidController->SetTunings(m_kp, m_ki, m_kd);
}

void LineFollowerRobot::moveForward(const uint32_t& speed)
{
    m_motorDriver->setSpeed(speed, speed);
}

void LineFollowerRobot::readLine()
{
    m_lineSensor->read(true);
}

bool LineFollowerRobot::readStopSensor()
{
    return m_lineSensor->readStopSensor();
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

    Serial << "X = " << m_lastPosition.x << "\t Y = " << m_lastPosition.y
           << " THETA = " << m_lastPosition.theta << endl;
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
    // TODO: Check if position is close to origin
    return false;
}

float LineFollowerRobot::linearSpeed()
{
    return m_linearSpeed;
}

float LineFollowerRobot::ki()
{
    return m_ki;
}

float LineFollowerRobot::kd()
{
    return m_kd;
}

float LineFollowerRobot::kp()
{
    return m_kp;
}

void LineFollowerRobot::incrementKi(float increment)
{
    m_ki += increment;
    updatePid();
}

void LineFollowerRobot::incrementKp(float increment)
{
    m_kp += increment;
    updatePid();
}

void LineFollowerRobot::incrementKd(float increment)
{
    m_kd += increment;
    updatePid();
}

void LineFollowerRobot::incrementSpeed(float increment)
{
    Serial << "CURRENT SPEED: " << m_linearSpeed << "\t INCREMENT" << increment;
    m_linearSpeed += increment;
    m_pidController->SetOutputLimits(-m_linearSpeed * 10, m_linearSpeed * 10);
}

void LineFollowerRobot::setKi(float ki)
{
    m_ki = ki;
}

void LineFollowerRobot::setKp(float kp)
{
    m_kp = kp;
}

void LineFollowerRobot::setKd(float kd)
{
    m_kd = kd;
}
void LineFollowerRobot::follow()
{
    this->follow(m_linearSpeed);
}

void LineFollowerRobot::follow(float speed)
{
    m_input = m_lineSensor->read(false);
    //m_output = m_fuzzyController->evaluate(m_input);
    m_pidController->Compute();

    int leftMotor = m_linearSpeed - m_output;
    int rightMotor = m_linearSpeed + m_output;

    m_motorDriver->setSpeed(leftMotor, rightMotor);

    //    Serial << "Input: " << m_input << "\t output: " << m_output << "\t Left: "
    //           << leftMotor << "\t Right: " << rightMotor << endl;
}

void LineFollowerRobot::stop()
{
    m_motorDriver->setSpeed(0, 0);
}

void LineFollowerRobot::setLinearSpeed(float linearSpeed)
{
    m_linearSpeed = linearSpeed;
    m_pidController->SetOutputLimits(-m_linearSpeed * 10, m_linearSpeed * 10);
}
