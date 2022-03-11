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
    servo->write(desired_pos);
    position = desired_pos;
}

void Swiveler::move_to_degree(int degree){
    servo->write(degree);
}