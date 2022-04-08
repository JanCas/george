#include <Arduino.h>

#include "config_values.h"
#include "ConfigParser.hpp"
#include "MotorEncoder.hpp"
#include "Module.hpp"

MotorEncoder motor_encoder(ena_pin, in1_pin, in2_pin, encoder_1_pin, encoder_2_pin, gear_ratio, encoder_counts);
ColorSensor color_sensor(red_pin, green_pin, blue_pin, phototransistor_pin);
Disk disk(&motor_encoder);
Swiveler swively(swiveler_pin);
HandSensor hand_sensor(hand_sensor_pin, threshold_hand_sensor);
MMQueue mm_queue(mm_queue_pins, emitter_pin);
LCD lcd(16,2);
HallSensor hall_sensor(hall_sensor_pin);

Module mod(BLUE, &mm_queue, &color_sensor, &hall_sensor, &swively, &disk, 12,13);
// ConfigParser config((const int[]) {41,43}, (const int[]) {45,47,49}, (const int[]) {51,55});


void setup(){
    // config.init();
    Serial.begin(9600);
    motor_encoder.set_pid_values(K_p, K_d,K_i,alpha);
    mod.init();
    // Serial.print("Setup done");
}

void loop() {
    mod.step();
}