#include "Swiveler.hpp"
#include <Arduino.h>

Swiveler::Swiveler(int servo_pin) {
    servo = new Servo();
    servo->attach(servo_pin);
}

Swiveler::~Swiveler() {
    servo->detach();
}

void Swiveler::move_to(position_enum desired_pos) {
    switch (desired_pos) {
        case CLOSED:
            servo->write(45);
            break;
    
        case BUCKET:
            servo->write(90);
            break;

        case NEXT_MODULE:
            servo->write(135);
            break;
    }
}