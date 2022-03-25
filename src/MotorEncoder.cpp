#include "MotorEncoder.hpp"


MotorEncoder::MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_pin1, int encoder_pin2, int gear_ratio, int count){
    this->ena_pin = ena_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->gear_ratio = gear_ratio;
    this->count = count;

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
    return constrain(speed, -255., 255.);
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
    
    pid(des_pos);

    Serial.print("pos: ");
    Serial.print(get_pos());
    Serial.print(" || ");
    Serial.println(speed);

    if (abs(get_pos() - des_pos ) < 5 && abs(speed) < 5){
        turn_off();
        return true;
    }
    return false;
}


double MotorEncoder::set_init_speed(double speed){
    this->speed = normalize_speed(speed);
    return this->speed;
}

void MotorEncoder::pid(double des){
    t_ms = micros(); // current time
    t = t_ms / 1000000.0;

    if (t > t_old + T_interval)
    {
        pos = get_pos();
        // Controller code
        delta_t = t - t_old;
        error = des - pos;
        integralError = integralError + error * delta_t;
        dErrordt = (error - error_old) / delta_t;
        dErrordtFilt = dErrordt * alpha + dError_filt_old * (1 - alpha);
        V = Kp * error + Kd * dErrordtFilt + Ki * integralError;

        dError_filt_old = dErrordtFilt;
        error_old = error;
        t_old = t;

        V = constrain(V, -255., 255.);
        speed = V;
        set_speed(V);
    }
}

void MotorEncoder::set_pid_values(double Kp, double Kd, double Ki, double alpha){
    this->alpha = alpha;
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;
}