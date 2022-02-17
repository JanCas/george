#include "Swiveler.hpp"
#include <Arduino.h>

Swiveler::Swiveler(int servo_pin) {
    servo = new Servo();
    servo->attach(servo_pin);
}

Swiveler::~Swiveler() {
    //servo->detach();
}

void Swiveler::move_to(position_enum desired_pos) {
    switch (desired_pos) {
        case CLOSED:
            servo->write(1);
            break;
    
        case BUCKET:
            servo->write(90);
            break;

        case NEXT_MODULE:
            servo->write(179);
            break;
    }
}

void Swiveler::sweep(){
    for (int i =0; i < 180; i++){
        servo->write(i);
        delay(15);
    }

    for (int i = 180; i > 0; i--){
        servo->write(i);
        delay(15);
    }
}