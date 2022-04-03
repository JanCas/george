#include <Arduino.h>

#include "Module.hpp"

char serialByte = '0';

MotorEncoder motor_encoder(12, 11, 10, 2, 3, 100, 12);
ColorSensor color_sensor(5, 6, 7, A0);
Disk disk(&motor_encoder);
Swiveler swively(8);
MMQueue mm_queue((const uint8_t[]){22, 36, 24, 38, 26, 40, 28, 42, 30, 44, 32, 46, 34}, 51);
LCD lcd(16,2);

// Module mod(BLUE, &mm_queue, &color_sensor, &swively, &disk, &lcd);

void setup()
{
    Serial.begin(9600);
    // motor_encoder.set_pid_values(.28, 0,.1,.05);
    motor_encoder.set_speed(15);
    // lcd.init();
    // swively.init();
    // mm_queue.init();
    // swively.move_to(NEXT_MODULE);
    // mod.init();
    // motor_encoder.set_speed(25);
    // motor_encoder.turn_on();
    // swively.move_to_degree(135);
    // motor_encoder.reset_time();
}

void loop()
{
    // if (Serial.available() > 0) {
    //     // get incoming byte:
    //     serialByte= Serial.read();
    // // Serial.print(serialByte);
    // // Serial.println(" ");
    // }

    // if (serialByte == 'g'){
    //     serialByte = '0';
    //     color_sensor.calibrate();
    //     Serial.println("------------------------------");
    // }
    // if (serialByte == 's'){
    //     serialByte = '0';
    //     Serial.println(color_sensor.color_to_string(color_sensor.get_color()));
    //     Serial.println("------------------------------");
    // }
    // mod.step();
    // if (disk.move_to_next()){ 
    //    delay(1000);
        // motor_encoder.reset_time();
    // }
}