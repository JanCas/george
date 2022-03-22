#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"
#include "Disk.hpp"
#include "Swiveler.hpp"
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include <LCD.hpp>
#include <QTRSensors.h>
#include "MMQueue.hpp"

bool running = false;

PID_controller pid(4, .7, 3.15, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);

double pos_des = 72.5;

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_speed(75);
/*
    Serial.write('a'); // this is to notify MATLAB that Arduino is ready to receive parameters
    String inString = "";
    while (Serial.available() == 0);
    inString = Serial.readStringUntil(' ');
    double Kp = inString.toFloat();
    inString = Serial.readStringUntil(' ');
    double Kd = inString.toFloat();
    inString = Serial.readStringUntil(' ');
    double Ki = inString.toFloat();
    inString = Serial.readStringUntil(' ');
    double StepSize = inString.toFloat();
    inString = Serial.readStringUntil(' ');
    double alpha = inString.toFloat();
    inString = Serial.readStringUntil(' ');
    double StepTime = inString.toFloat();

    pos_des = StepSize;
    pid.set_config_values(Kp, Kd, Ki, alpha, StepTime);
    double t0 = micros() / 1000000.;
    */
   motor_encoder.set_speed_constrain(255);
}

void loop()
{

    // motor_encoder.drive_to(pos_des); 
}