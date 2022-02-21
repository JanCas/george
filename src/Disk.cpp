#include "Disk.hpp"


Disk::Disk(MotorEncoder *motor) {
    this->motor = motor;
}

Disk::~Disk() {
    delete motor;
}

void Disk::move_to(disk_position_enum des_position) {
    
}

bool Disk::move_to_next() {
    
}

void Disk::pause() {
    
}
