#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>

#define NUM_SENSORS 6
#define TIMEOUT 2500
#define EMITTER_PIN 27

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
};

#endif // LINESENSOR_H
