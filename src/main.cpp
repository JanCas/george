#include <Arduino.h>

#include "ConfigParser.hpp"
#include "MotorEncoder.hpp"

bool running = true;
int downstream_pin = 8;
int button_pin = 13;
int led_pin = 6;

// ConfigParser config((const int[]) {41,43}, (const int[]) {45,47,49}, (const int[]) {51,55});

MotorEncoder motor_encoder(12,11,10,2,3,380,12);


void setup(){
    // config.init();
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(13, INPUT);
    pinMode(8, INPUT);
    pinMode(6, OUTPUT);
    // motor_encoder.set_speed(45);
    // motor_encoder.set_pid_values
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