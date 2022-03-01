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

double MotorEncoder::set_speed(double speed) {

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

double MotorEncoder::normalize_speed(double speed) {
    return constrain(speed, -255, 255);
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
    
    // Serial.print("pos: ");
    // Serial.print(curr_pos);
    // Serial.print(" || vel: ");
    // Serial.println(new_vel);

    set_speed(new_vel);

    if (abs(des_pos - curr_pos) < 1 && abs(new_vel) < 3){ // as long as the position is within one degree and the abs(velocity) is less then 3 
        return true;
    }

    return false;
}

double MotorEncoder::pid_compute(int des_pos, int constraint){
    return pid_controller->compute(get_pos(), des_pos, constraint);
}

double MotorEncoder::set_init_speed(double speed){
    this->speed = normalize_speed(speed);
    return this->speed;
}