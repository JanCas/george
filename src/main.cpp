#include <Arduino.h>

// #include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"

MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12);
PID_controller pid(50.0, .3, 1.0, 1.0, 1.0, .75);

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_speed(30);
    motor_encoder.turn_on();
}

void loop()
{   
    if (Serial.read() == 'p'){
        motor_encoder.turn_off();
    }
    if (Serial.read() == 'y'){
        motor_encoder.turn_on();
    }
    Serial.println(motor_encoder.get_pos());
    Serial.println(pid.compute(motor_encoder.get_pos(), 72));
}