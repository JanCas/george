#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <LCD.hpp>
#include <QTRSensors.h>
#include "MMQueue.hpp"

bool running = false;

MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12);

double pos_des = 72.5;

void setup()
{
    Serial.begin(9600);
}

void loop()
{

    // motor_encoder.drive_to(pos_des); 
}