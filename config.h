#ifndef CONFIG_H
#define CONFIG_H

const int linearSpeed = 800;

const double consKp = 64;
const double consKd = 0;
const double consKi = 0;

//const int linearSpeed = 500;

//const double consKp = 40;
//const double consKd = 0;
//const double consKi = 0;
///< Line-sensor
#define WHITE_LINE 0

#define NUM_SENSORS 6
#define TIMEOUT 2500
#define EMITTER_PIN 27

#endif // CONFIG_H
