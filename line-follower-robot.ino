/*
Project:	line-follower-robot
MCU: Arduino Uno

Created using QtCreator
*/

#include "linefollowerrobot.h"
#include "util/util.h"
#include <Arduino.h>

#include "BluetoothSerial.h"
#include "EEPROM.h"
#include "cmdmessenger.h"
#include "linesensor.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

enum Commands {
    SetKP = 0,
    SetKI = 1,
    SetKD = 2,
    SetMaxSpeed = 3,
    SetMaxTime = 4,
    Calibrate = 5,
    Start = 9,
    Stop = 10,
    SaveConfigs = 11,
    LoadConfigs = 12,
    SwitchControlMode = 13,
    AutoTunePID = 14,
    Save = 15,
};

struct Configs {
    float kP, kI, kD, SPEED;
};

Configs configs;
LineFollowerRobot lineFollower;
ElapsedTimer timer;
BluetoothSerial SerialBT;
CmdMessenger cmdMessenger = CmdMessenger(SerialBT, ',', 'j', '/');

void onSetKpCommand(CmdMessenger* messenger);
void onSetKdCommand(CmdMessenger* messenger);
void onSetKiCommand(CmdMessenger* messenger);
void onSetMaxSpeedCommand(CmdMessenger* messenger);
void onStartCommand(CmdMessenger* messenger);
void onStopCommand(CmdMessenger* messenger);
void onSaveCommand(CmdMessenger* messenger);
void onCalibrateCommand(CmdMessenger* messenger);

bool following = true;
void setup()
{
    Serial.begin(460800);
    lineFollower.init();
    SerialBT.begin("jack da VK");

    if (!EEPROM.begin(EEPROM.length() - 1)) {
        Serial.println("failed to initialise EEPROM");
        delay(1000000);
    }

    configs.kP = EEPROM.readFloat(BYTE_KP);
    configs.kI = EEPROM.readFloat(BYTE_KI);
    configs.kD = EEPROM.readFloat(BYTE_KD);
    configs.SPEED = EEPROM.readFloat(BYTE_SPEED);

    Serial << "KP: " << configs.kP << endl;
    Serial << "KI: " << configs.kI << endl;
    Serial << "kD: " << configs.kD << endl;
    Serial << "SPEED: " << configs.SPEED << endl;

    lineFollower.setKp(configs.kP);
    lineFollower.setKi(configs.kI);
    lineFollower.setKd(configs.kD);
    lineFollower.setLinearSpeed((configs.SPEED != configs.SPEED) ? 500 : configs.SPEED);
    lineFollower.updatePid();

    cmdMessenger.attach(Commands::SetKP, onSetKpCommand);
    cmdMessenger.attach(Commands::SetKI, onSetKiCommand);
    cmdMessenger.attach(Commands::SetKD, onSetKdCommand);
    cmdMessenger.attach(Commands::SetMaxSpeed, onSetMaxSpeedCommand);
    cmdMessenger.attach(Commands::Start, onStartCommand);
    cmdMessenger.attach(Commands::Stop, onStopCommand);
    cmdMessenger.attach(Commands::Save, onSaveCommand);
    cmdMessenger.attach(Commands::Calibrate, onCalibrateCommand);

    lineFollower.waitButtonPress();
    lineFollower.calibrate();
    delay(2000);
}

int numberOfCheckpoints = 0;
bool shouldStop = false;
long stopTime = 0;
void loop()
{
    cmdMessenger.feedinSerialData();

    if (following) {
        lineFollower.follow();

        if (lineFollower.readStopSensor()) {
            numberOfCheckpoints++;

            if (numberOfCheckpoints >= 10) {
                shouldStop = true;
                stopTime = millis();
            }
        }
        if (shouldStop == true && (millis() - stopTime > 300)) {
            lineFollower.stop();
            following = false;
        }

    } else {
    }
}

void onSetKpCommand(CmdMessenger* messenger)
{
    char signal = messenger->readCharArg();
    float increment = messenger->readFloatArg();
    if (signal == '+') {
        lineFollower.incrementKp(increment);
    } else {
        if (lineFollower.kd() - increment < 0)
            lineFollower.setKd(0);
        lineFollower.incrementKp(-increment);
    }

    Serial << "Incremente Kp: " << signal << increment << endl;
    Serial << "Kp: " << lineFollower.kp() << endl;
}
void onSetKdCommand(CmdMessenger* messenger)
{
    char signal = messenger->readCharArg();
    float increment = messenger->readFloatArg();
    if (signal == '+') {
        lineFollower.incrementKd(increment);

    } else {
        lineFollower.incrementKd(-increment);
    }

    Serial << "Incremente Kd: " << signal << increment << endl;
    Serial << "Kd: " << lineFollower.kd() << endl;
}
void onSetKiCommand(CmdMessenger* messenger)
{
    char signal = messenger->readCharArg();
    float increment = messenger->readFloatArg();
    if (signal == '+') {
        lineFollower.incrementKi(increment);
    } else {
        lineFollower.incrementKi(-increment);
    }

    Serial << "Incremente Ki: " << signal << increment << endl;
    Serial << "Ki: " << lineFollower.ki() << endl;
}
void onSetMaxSpeedCommand(CmdMessenger* messenger)
{
    char signal = messenger->readCharArg();
    float increment = messenger->readFloatArg();
    if (signal == '+') {
        lineFollower.incrementSpeed(increment);
    } else {
        lineFollower.incrementSpeed(-increment);
    }

    Serial << "Incremente Speed: " << signal << increment << endl;
    Serial << "Speed: " << lineFollower.linearSpeed() << endl;
}
void onStartCommand(CmdMessenger* messenger)
{
    Serial << "START!" << endl;
    following = true;
    shouldStop = false;
    numberOfCheckpoints = 0;

    delay(1000);
}

void onStopCommand(CmdMessenger* messenger)
{
    Serial << "STOP!" << endl;
    following = false;
    numberOfCheckpoints = 0;
    lineFollower.stop();
}

void onSaveCommand(CmdMessenger* messenger)
{
    EEPROM.writeFloat(BYTE_KP, lineFollower.kp());
    EEPROM.writeFloat(BYTE_KI, 0.0);
    EEPROM.writeFloat(BYTE_KD, lineFollower.kd());
    EEPROM.writeFloat(BYTE_SPEED, lineFollower.linearSpeed());

    EEPROM.commit();

    Serial << "SAVE!" << endl;

    Serial << "lineFollower KP: " << lineFollower.kp() << endl;
    Serial << "EEPROM KP: " << EEPROM.readFloat(BYTE_KP) << endl;

    Serial << "lineFollower KI: " << lineFollower.ki() << endl;
    Serial << "EEPROM KI: " << EEPROM.readFloat(BYTE_KI) << endl;

    Serial << "lineFollower KD: " << lineFollower.kd() << endl;
    Serial << "EEPROM KD: " << EEPROM.readFloat(BYTE_KD) << endl;

    Serial << "lineFollower SPEED: " << lineFollower.linearSpeed() << endl;
    Serial << "EEPROM SPEED: " << EEPROM.readFloat(BYTE_SPEED) << endl;
}

void onCalibrateCommand(CmdMessenger* messenger)
{
    lineFollower.stop();
    lineFollower.calibrate();
}
