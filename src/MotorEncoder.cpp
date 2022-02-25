#include "MotorEncoder.hpp"


MotorEncoder::MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_a_pin1, int encoder_a_pin2, int gear_ratio, int count) {
    this->ena_pin = ena_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->gear_ratio = gear_ratio;
    this->count = count;


    this->encoder_a = new Encoder(encoder_a_pin1, encoder_a_pin2);

    pinMode(this->ena_pin, OUTPUT);
    pinMode(this->in1_pin, OUTPUT);
    pinMode(this->in2_pin, OUTPUT);

    digitalWrite(this->in1_pin, HIGH);
    digitalWrite(this->in2_pin, LOW);

    this->speed = 0;
    deg_per_count =(float) (360.0 / (count*gear_ratio));
    direction_clockwise = true;
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

    if (speed < 0){
        ccw();
        speed = abs(speed);
    }else if (speed > 0){
        cw();
    }

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
    }else if (speed < -255){
        return -255;
    }

    return speed;
}

void MotorEncoder::ccw(){
    if (!direction_clockwise){
        digitalWrite(this->in1_pin, LOW);
        digitalWrite(this->in2_pin, HIGH);
        direction_clockwise = true;
    }
}

void MotorEncoder::cw(){
    if (direction_clockwise){
        digitalWrite(this->in1_pin, HIGH);
        digitalWrite(this->in2_pin, LOW);
        direction_clockwise = false;
    }
}

float MotorEncoder::get_pos(){
    return deg_per_count * encoder_a->read();
}

void MotorEncoder::flip_direction(){
    if (direction_clockwise){
        ccw();
    } else {
        cw();
    }
}