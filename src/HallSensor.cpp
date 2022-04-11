#include "HallSensor.hpp"


HallSensor::HallSensor(int pin) {
    this->pin = pin;    
}

HallSensor::~HallSensor() {
    
}

bool HallSensor::sense() {
    return digitalRead(pin) == HIGH;
}