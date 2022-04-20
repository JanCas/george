#include "HandSensor.hpp"


HandSensor::HandSensor(int analog_pin, int limit) {
    this->analog_pin = analog_pin;
    this->limit = limit;
}

HandSensor::~HandSensor() {

}

void HandSensor::init() {
    pinMode(analog_pin, INPUT);
    Serial.println(limit);
}

bool HandSensor::is_hand() {
    // Serial.println(analogRead(analog_pin));
    return analogRead(analog_pin) > limit;
}
