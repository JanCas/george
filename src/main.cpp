#include <Arduino.h>

#include "ConfigParser.hpp"

ConfigParser config((const int[]) {41,43}, (const int[]) {45,47,49}, (const int[]) {51,55});

void setup(){
    // config.init();
    Serial.begin(9600);
    pinMode(5, INPUT);
    pinMode(A0, INPUT);
}

void loop() {
    Serial.println(analogRead(A0));
    // if (config.read(1)){
    //     Serial.print(config.get_color());
    //     Serial.print(" || ");
    //     Serial.println(config.get_queue_size());
    // }
}