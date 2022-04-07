#include <Arduino.h>

#include "ConfigParser.hpp"
#include "MotorEncoder.hpp"
#include "Module.hpp"

bool running = true;
int downstream_pin = 8;
int button_pin = 13;
int led_pin = 6;

MotorEncoder motor_encoder(12, 11, 10, 2, 3, 380, 12);
ColorSensor color_sensor(5, 6, 7, A0);
Disk disk(&motor_encoder);
Swiveler swively(8);
MMQueue mm_queue((const uint8_t[]){22, 36, 24, 38, 26, 40, 28, 42, 30, 44, 32, 46, 34}, 51);
LCD lcd(16,2);
// ConfigParser config((const int[]) {41,43}, (const int[]) {45,47,49}, (const int[]) {51,55});

MotorEncoder motor_encoder(12,11,10,2,3,380,12);


void setup(){
    // config.init();
    Serial.begin(9600);
    motor_encoder.set_pid_values(2.4, .21,0,1);
    pinMode(A0, INPUT);
    pinMode(13, INPUT);
    pinMode(8, INPUT);
    pinMode(6, OUTPUT);
    // motor_encoder.set_speed(45);
}

void loop() {
    int hand_value = analogRead(A0);
    Serial.println(hand_value);
    if (hand_value > 250){
        running = false;
    }
    if (digitalRead(downstream_pin) == HIGH){
       running = false;
       Serial.println("HERE");
    }
    if (!running){
        motor_encoder.turn_off();
        Serial.println("sending other modules to stop");
        if (digitalRead(button_pin) == HIGH){
            running = true;
            digitalWrite(led_pin, LOW);
        }
    }
    else{
        motor_encoder.turn_on();
    }
}