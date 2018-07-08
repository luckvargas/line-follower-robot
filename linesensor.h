#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "config.h"
#include "util/elapsedtimer.h"
#include <QTRSensors.h>

class LineSensor {
public:
    LineSensor();
    float read(bool print);
    bool readStopSensor();
    void calibrate();

private:
    float readLine();
    QTRSensorsRC* m_qtrSensors;
    QTRSensorsRC* m_qtrSecondSensor;
    unsigned int m_sensorValues[NUM_SENSORS];
    unsigned int m_secondSensorValues[NUM_SECOND_SENSOR];

    bool m_calibrated = false;
    long m_readTime;
    ///< Constants
    unsigned char sensorPins[NUM_SENSORS] = { 14, 12, 32, 33, 25, 26 };
    unsigned char SecondSensorPins[NUM_SECOND_SENSOR] = { 22 };
    float map(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif // LINESENSOR_H
