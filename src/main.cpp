#include <Arduino.h>

#include "Swiveler.hpp"

Swiveler *swiveler = new Swiveler(7);
int i = 0;

void setup() {
    Serial.begin(9600);
    swiveler->init();
}

void loop() {
    position_enum possible[] = {CLOSED, BUCKET, NEXT_MODULE};


    for (position_enum pos : possible)
    {
        Serial.print("Moving to: ");
        Serial.println(pos);
        swiveler->move_to(pos);
        Serial.println();
        delay(2000);
    }
}