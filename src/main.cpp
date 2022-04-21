#include <Arduino.h>

#include "config/config_values_2.h"
#include "ConfigParser.hpp"
#include "MotorEncoder.hpp"
#include "Module.hpp"

MotorEncoder *hopper_motor = is_top ? new MotorEncoder(enb_pin, in3_pin, in4_pin) : NULL;

// if (is_top){
//     hopper_motor = new MotorEncoder(enb_pin, in3_pin, in4_pin);
// }

MotorEncoder motor_encoder(ena_pin, in1_pin, in2_pin, encoder_1_pin, encoder_2_pin, gear_ratio, encoder_counts);
ColorSensor color_sensor(red_pin, green_pin, blue_pin, phototransistor_pin);
Disk disk(&motor_encoder);
Swiveler swively(swiveler_pin);
HandSensor hand_sensor(hand_sensor_pin, threshold_hand_sensor);
MMQueue mm_queue(mm_queue_pins, emitter_pin);

ConfigParser config(module_adress, adress_pins, sorting_color_pins, queue_size_pins);
Module mod(BLUE, &mm_queue, &color_sensor, &swively, &disk, &config, &hand_sensor, hopper_motor, e_stop_pin, start_stop_button_pin,
            power_led, sorting_active_led, sorting_paused_led, sorting_disabled_led);

bool running = false;

int num_rotations_for_sensing = 5;
int i = 0;

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_pid_values(K_p, K_d,K_i,alpha);
    mod.init();
}

void loop() {

    mod.step();
}