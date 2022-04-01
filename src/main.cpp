#include <Arduino.h>

#include "ConfigParser.hpp"

ConfigParser config((const int[]) {1,2}, (const int[]) {3,4,5}, (const int[]) {6,7});

void setup(){
    config.init();
}

void loop() {
    if (config.read(1)){
        Serial.print(config.get_color());
        Serial.print(" || ");
        Serial.println(config.get_queue_size());
    }
}