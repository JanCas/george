#include <Arduino.h>

#include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "PID_controller.hpp"
#include "Module.hpp"

cppQueue queue(sizeof(mm_attr), 2, FIFO, true);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12);
PID_controller pid(10, .04, 2.0, 1.0, 1.0, .075);

bool cw = true;

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_speed(50);
    motor_encoder.turn_on();
}


void loop()
{

    double pos = motor_encoder.get_pos();
    double new_vel = pid.compute(pos, 360, 30);
    // Serial.print("pos: ");
    // Serial.print(pos);
    // Serial.print(" || ");
    // Serial.println(new_vel);
    motor_encoder.set_speed((int) new_vel);

    Serial.println(pos);
}
