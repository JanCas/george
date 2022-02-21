#include <Arduino.h>

// #include "cppQueue.h"
#include "Module.hpp"
#include "MotorEncoder.hpp"


MotorEncoder motor_encoder(12, 11, 10, 20, 21, 20, 53, 380, 12, 1);
// cppQueue *queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);

void setup() {
    Serial.begin(9600);
    motor_encoder.set_speed(130);
    motor_encoder.turn_on();
}

void loop() {
    Serial.println(motor_encoder.get_pos());
}