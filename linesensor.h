#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>
#define NUM_SENSORS 6

class LineSensor {
public:
    LineSensor();
    int read(bool print);
    void calibrate();

private:
    QTRSensorsRC m_qtrSensors;
    unsigned int m_sensorValues[NUM_SENSORS];

    ///< Constants
    unsigned char sensorPins[NUM_SENSORS] = { 2, 3, 4, 5, 6, 7 };
};

#endif // LINESENSOR_H
