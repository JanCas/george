#include "Swiveler.hpp"
#include <Arduino.h>

Swiveler::Swiveler(int servo_pin) {
    pin_num = servo_pin;
    servo = new Servo();
}

void Swiveler::init(){
    servo->attach(pin_num);
}

Swiveler::~Swiveler() {
    servo->detach();
    delete servo;
}

void Swiveler::move_to(swiveler_position_enum desired_pos) {
    
    position = desired_pos;
    
    switch (desired_pos) {
        case CLOSED:
            servo->write(0);
            break;
    
        case BUCKET:
            servo->write(90);
            break;

        case NEXT_MODULE:
            servo->write(180);
            break;
    }
}