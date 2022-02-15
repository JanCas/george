#include "MotorEncoder.hpp"


MotorEncoder::MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_a_pin1, int encoder_a_pin2, int encoder_b_pin1, int encoder_b_pin2) {
    this->ena_pin = ena_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->encoder_a = new Encoder(encoder_a_pin1, encoder_a_pin2);
    this->encoder_b = new Encoder(encoder_b_pin1, encoder_b_pin2);

    pinMode(this->ena_pin, OUTPUT);
    pinMode(this->in1_pin, OUTPUT);
    pinMode(this->in2_pin, OUTPUT);

    digitalWrite(this->in1_pin, HIGH);
    digitalWrite(this->in2_pin, LOW);

    this->speed = 0;    
}

MotorEncoder::~MotorEncoder() {
    delete this->encoder_a;
    delete this->encoder_b;
}

void MotorEncoder::reset() {
    this->encoder_a->write(0);
    this->encoder_b->write(0);    
}

void MotorEncoder::turn_on() {
    analogWrite(this->ena_pin, this->speed);
}

int MotorEncoder::set_speed(int speed) {
    speed = normalize_speed(speed);

    this->speed = speed;

    analogWrite(this->ena_pin, speed);

    return speed;

}

void MotorEncoder::turn_off() {
    analogWrite(this->ena_pin, 0);
}

int MotorEncoder::normalize_speed(int speed) {
    if (speed > 255){
        return 255;
    }else if (speed < 0){
        return 0;
    }

    return speed;
}

void MotorEncoder::cw(){
    digitalWrite(this->in1_pin, LOW);
    digitalWrite(this->in2_pin, HIGH);
}

void MotorEncoder::ccw(){
    digitalWrite(this->in1_pin, HIGH);
    digitalWrite(this->in2_pin, LOW);
}

long MotorEncoder::encoder_a_count(){
    return this->encoder_a->read();
}

long MotorEncoder::encoder_b_count(){
    return this->encoder_b->read();
}

void MotorEncoder::write(int pos){
    this->encoder_a->write(pos);
    //TODO: this is not done yet
}