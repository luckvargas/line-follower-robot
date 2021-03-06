#ifndef LINEFOLLOWERROBOT_H
#define LINEFOLLOWERROBOT_H

#include "config.h"
#include "util/util.h"
#include <Arduino.h>

#ifdef __AVR__
#include <StandardCplusplus.h>
#endif
#include <vector>

class Button;
class LineSensor;
class MotorDriver;
class FuzzyController;
class PID;

#define BYTE_KP 0
#define BYTE_KI 5
#define BYTE_KD 10
#define BYTE_SPEED 15

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

struct LaneSegment {
    LaneSegment() {}

    LaneSegment(float length, float radius)
    {
        this->length = length;
        this->radius = radius;
    }

    float length;
    float radius;
};

class LineFollowerRobot {
public:
    LineFollowerRobot();

    void init();

    void moveForward(const uint32_t& speed);

    void readLine();

    bool readStopSensor();

    void readOdometry();

    void scan();

    void follow();

    void follow(float speed);

    void setLinearSpeed(float linearSpeed);

    void calibrate();

    void waitButtonPress();

    void stop();

    void setKp(float kp);

    void setKd(float kd);

    void setKi(float ki);

    void incrementKp(float increment);
    void incrementKd(float increment);
    void incrementKi(float increment);
    void incrementSpeed(float increment);

    float kp();

    float kd();

    float ki();

    float linearSpeed();

    void updatePid();

private:
    bool closeToOrigin();

    ///< Periferics
    MotorDriver* m_motorDriver;
    LineSensor* m_lineSensor;
    FuzzyController* m_fuzzyController;
    PID* m_pidController;
    Button* m_startButton;
    ElapsedTimer m_timer;

    ///< State variables
    bool m_calibrated;

    ///< Control variables
    double m_input;
    double m_output;
    double m_setpoint = 0;

    ///< Speed parameters
    int m_maxSpeed;
    float m_linearSpeed;

    ///< Controler Values
    float m_kp;
    float m_kd;
    float m_ki;

    ///< Odometry and Mapping
    std::vector<LaneSegment> m_lane;
    Position m_lastPosition;
    Pair<uint32_t, uint32_t> m_lastEncoderRead;

    ///< Constraints
    const uint8_t startButtonPin = 19;
    const uint8_t indicatorLedPin = 15;
    const float distanceBetweenWheels = 100.0; // Distance between wheels - 10cm
    const float countsPerCentimeter = 100.0;
    const float scanSpeed = 1000.0;
};
#endif // LINEFOLLOWERROBOT_H
