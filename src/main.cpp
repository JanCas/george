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
HallSensor hall_sensor(hall_sensor_pin);

ConfigParser config(module_adress, adress_pins, sorting_color_pins, queue_size_pins);
Module mod(BLUE, &mm_queue, &color_sensor, &hall_sensor, &swively, &disk, &config, upstream_pin,downstram_pin);

void setup(){
    Serial.begin(9600);
    motor_encoder.set_pid_values(K_p, K_d,K_i,alpha);
    motor_encoder.set_speed(50);
}

void loop() {
    if (motor_encoder.get_pos() < 0) motor_encoder.turn_off();
    Serial.println(motor_encoder.get_pos());
}