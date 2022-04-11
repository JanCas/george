#include "Disk.hpp"


Disk::Disk(MotorEncoder *motor, int limit_switch_pin) {
    this->motor = motor;
    curr_position = COLLECTION;
    next_position = HALL_SENSOR;
    this->limit_switch_pin = limit_switch_pin;
}

Disk::~Disk() {
    delete motor;
}

void Disk::init(){
    pinMode(limit_switch_pin, INPUT);
}

bool Disk::move_to(disk_position_enum des_position) {

    int des_pos_continous = rotation_num * 360 + des_position;

    if (motor->drive_to(des_pos_continous)){
        update_position(des_position);
        return true;
    }
    return false;    
}

void Disk::reset_time(){
    motor->reset_time();
}

void Disk::update_position(disk_position_enum pos) {
    
    curr_position = pos;
    
    switch (pos)
    {
    case COLLECTION:
        next_position = HALL_SENSOR;
        break;
    
    case HALL_SENSOR:
        next_position = COLOR_SENSOR;
        break;
    
    case COLOR_SENSOR:
        next_position = TRASH;
        break;

    case TRASH:
        next_position = LAST;
        break;
    
    case LAST:
        next_position = END;
        break;
    
    case END:
        next_position = HALL_SENSOR;
        rotation_num++;
        // motor->reset();
        break;
    
    default:
        break;
    }
}

bool Disk::move_to_next() {
    return move_to(next_position);
}

void Disk::pause() {
    motor->turn_off();
}

void Disk::continue_disk(){
    motor->reset_time();
}

void Disk::drive_to_zero(){
    motor->set_speed(30);
    motor->turn_on();
    while(!digitalRead(limit_switch_pin)){}
    motor->turn_off();
    motor->reset();
}
