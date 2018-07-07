#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "config.h"
#include <QTRSensors.h>

class LineSensor {
public:
    LineSensor();
    float read(bool print);
    void calibrate();

private:
    float readLine();
    QTRSensorsRC* m_qtrSensors;
    unsigned int m_sensorValues[NUM_SENSORS];

    bool m_calibrated = false;

    ///< Constants
    unsigned char sensorPins[NUM_SENSORS] = { 14, 12, 32, 33, 25, 26 };
    float map(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif // LINESENSOR_H
