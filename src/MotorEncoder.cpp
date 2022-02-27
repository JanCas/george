#include "MotorEncoder.hpp"


MotorEncoder::MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_pin1, int encoder_pin2, int gear_ratio, int count, PID_controller *pid_controller) {
    this->ena_pin = ena_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->gear_ratio = gear_ratio;
    this->count = count;

    this->pid_controller = pid_controller;
    this->encoder = new Encoder(encoder_pin1, encoder_pin2);

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
    delete this->encoder;
}

void MotorEncoder::reset() {
    this->encoder->write(0);
}

void MotorEncoder::turn_on() {
    analogWrite(this->ena_pin, this->speed);
}

int MotorEncoder::set_speed(int speed) {

    if (speed < 0){
        ccw();
        speed = abs(speed);
    }else if (speed > 0){
        cw();
    }

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
    return deg_per_count * encoder->read();
}

bool MotorEncoder::drive_to(int des_pos){
    double curr_pos = get_pos();
    double new_vel = pid_controller->compute(curr_pos, des_pos, speed);
    
    set_speed((int) new_vel);

    if (abs(des_pos - curr_pos) < 1 && new_vel == 0){ // as long as the position is within one degree and the velocity is 0
        return true;
    }

    return false;
}