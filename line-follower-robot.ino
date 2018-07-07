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
    lineFollower.calibrate();
    delay(2000);
}

void loop()
{
    //timer.start();
    lineFollower.follow();
    //lineFollower.readLine();
    //Serial << "delta time: " << timer.elapsed() << endl;
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
