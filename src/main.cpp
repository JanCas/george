#include <Arduino.h>

#include "config_values.h"
#include "ConfigParser.hpp"
#include "MotorEncoder.hpp"
#include "Module.hpp"

MotorEncoder motor_encoder(ena_pin, in1_pin, in2_pin, encoder_1_pin, encoder_2_pin, gear_ratio, encoder_counts);
ColorSensor color_sensor(red_pin, green_pin, blue_pin, phototransistor_pin);
Disk disk(&motor_encoder, limit_switch_pin);
Swiveler swively(swiveler_pin);
HandSensor hand_sensor(hand_sensor_pin, threshold_hand_sensor);
MMQueue mm_queue(mm_queue_pins, emitter_pin);
HallSensor hall_sensor(hall_sensor_pin);

ConfigParser config(module_adress, adress_pins, sorting_color_pins, queue_size_pins);
Module mod(BLUE, &mm_queue, &color_sensor, &hall_sensor, &swively, &disk, &config, upstream_pin, downstram_pin);

bool running = false;

int num_rotations_for_sensing = 5;
int i = 0;

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_pid_values(K_p, K_d, K_i, alpha);
    pinMode(start_stop_button_pin, INPUT);
    // motor_encoder.set_speed(40);
    // mod.init();
    // mod.calibrate();
}

void loop()
{
    // color_sensor.turn_blue();
    // delay(1000);

    // color_sensor.turn_red();
    // delay(1000);

    // color_sensor.turn_green();
    // delay(1000);

    // delay(5000);
    // mod.step();
    if (!running)
    {
        if (digitalRead(start_stop_button_pin))
        {
            running = true;
            disk.reset_time();
        }
    }

    if (running)
    {
        if (disk.move_to_next())
        {
            if (i >= 1) color_sensor.calibrate();
            delay(2000);
            disk.reset_time();
            i++;
        }
        if (i > num_rotations_for_sensing)
        {
            running=false;
        }
    }
}