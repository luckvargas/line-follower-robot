/*
Project:	line-follower-robot
MCU: Arduino Uno

Created using QtCreator
*/

#include "linefollowerrobot.h"
#include "util/util.h"
#include <Arduino.h>

LineFollowerRobot lineFollower;
ElapsedTimer timer;

void setup()
{
    Serial.begin(115200);
    lineFollower.init();

    Serial << "Press button to start..." << endl;
    lineFollower.waitButtonPress();
    Serial << "Press button to start..." << endl;

    lineFollower.calibrate();
}

void loop()
{
    timer.start();
    lineFollower.follow();
    Serial << timer.elapsed() << endl;
}

int main()
{
    // Initialize Arduino Librairies
    init();
    setup();
    while (1) {
        loop();
    }
}