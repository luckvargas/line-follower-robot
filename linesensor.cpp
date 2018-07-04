#include "linesensor.h"
#include "util/util.h"

LineSensor::LineSensor()
{
    m_qtrSensors = new QTRSensorsRC(sensorPins, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
}

float LineSensor::read(bool print)
{
    float position = 0;
    if (m_calibrated) {
        position = m_qtrSensors->readLine(m_sensorValues);
    } else {
        position = this->readLine();
    }

    if (print) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            Serial << m_sensorValues[i] << "\t";
        }
        Serial << " - Position: " << position << endl;
    }

    return position;
}

void LineSensor::calibrate()
{
    m_qtrSensors->calibrate();
    m_calibrated = true;
}

float LineSensor::readLine()
{
    float position = 0;
    float sum = 0;
    m_qtrSensors->read(m_sensorValues);
    for (int i = 0; i < NUM_SENSORS; i++) {
        position += (i * TIMEOUT) * (TIMEOUT - m_sensorValues[i]);
        sum += (TIMEOUT - m_sensorValues[i]);
    }
    if (sum == 0)
        return 0;
    position = position / sum - TIMEOUT * (NUM_SENSORS - 1) / 2;
    position = (position / (TIMEOUT * (NUM_SENSORS - 1) / 2)) * 10;

    return position;
}
