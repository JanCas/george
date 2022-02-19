#include <Arduino.h>

#include "Swiveler.hpp"
#include "avr8-stub.h"

Swiveler swiveler(7);

void setup() {
    
    debug_init();
}

void loop() {
    breakpoint();
    position_enum possible[] = {CLOSED, BUCKET, NEXT_MODULE};
    
    for(position_enum pos : possible){
        breakpoint();
        swiveler.move_to(pos);
        delay(500);
    }

}