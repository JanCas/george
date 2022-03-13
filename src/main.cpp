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

Swiveler *swively = new Swiveler(8);
cppQueue *mm_command_queue = new cppQueue(sizeof(mm_attr), 2, FIFO, true);
PID_controller pid(.35, 0, .08, .075);
MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, &pid);
// LCD lcd(16,2);
int delayTime = 100;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_init_speed(50);
    motor_encoder.turn_on();
}

void loop()
{
}
