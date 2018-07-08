#ifndef CONFIG_H
#define CONFIG_H

//const int linearSpeed = 800;

//const double consKp = 64;
//const double consKd = 0;
//const double consKi = 0;

const int linearSpeed = 500;
const double consKp = 40;
const double consKd = 0;
const double consKi = 0;

///< Line-sensor
#define WHITE_LINE 1
#define NUM_SENSORS 6
#define TIMEOUT 3000
#define EMITTER_PIN 27

#define NUM_SECOND_SENSOR 2
#define SECOND_SENSOR_TIMEOUT 3000
#define EMITTER_PIN_SECOND_SENSOR 27

#endif // CONFIG_H
