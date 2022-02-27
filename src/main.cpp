#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"

PID_controller pid(0.368, .028, 0.0046, 0.7833, 1.0, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_speed(50);
    motor_encoder.turn_on();
}


void loop()
{
    if (motor_encoder.drive_to(72)){
        
    }
}
