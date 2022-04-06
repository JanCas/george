#include <Arduino.h>

#include "Module.hpp"

char serialByte = '0';

MotorEncoder motor_encoder(12, 11, 10, 2, 3, 380, 12);
ColorSensor color_sensor(5, 6, 7, A0);
Disk disk(&motor_encoder);
Swiveler swively(8);
MMQueue mm_queue((const uint8_t[]){22, 36, 24, 38, 26, 40, 28, 42, 30, 44, 32, 46, 34}, 51);
LCD lcd(16,2);

// Module mod(BLUE, &mm_queue, &color_sensor, &swively, &disk, &lcd);

void setup()
{
    Serial.begin(9600);
    // motor_encoder.set_pid_values(.38, 0,.05,.05);
    motor_encoder.set_pid_values(2.4, .21,0,1);
}

void loop()
{
    if (disk.move_to_next()){ 
       delay(1000);
        motor_encoder.reset_time();
    }
}