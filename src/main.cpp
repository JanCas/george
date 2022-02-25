#include <Arduino.h>

// #include "cppQueue.h"
#include "MotorEncoder.hpp"
#include "Disk.hpp"
#include <PID_v1.h>

MotorEncoder motor_encoder(12, 11, 10, 20, 21, 380, 12, 1);

unsigned long t_ms = 0;
double Pos, Vel;
double Pos_old = 0, Vel_old = 0;
double Pos_des;
double V; // motor voltage command
double t, t_old = 0, t0, delta_t;
double T_motor = 0;
double Kp = 50, Kd = 0.1, Ki=3; // PID gains
double error, dErrordt, integralError = 0, errorOld, dErrordtFilt, dErrordtFilt_old;
double StepSize;
double alpha; // digital filter weight
double StepTime;
float position;

void pid()
{
    unsigned long t_ms = micros();
    unsigned long t = t_ms / 1000000.0; // current time

    if (t > t_old + T_motor)
    {

        // Encoder sensing
        position = motor_encoder.get_pos();
        Pos_des = 450;

        // Controller code
        delta_t = t - t_old;
        error = Pos_des - position;
        integralError = integralError + error * delta_t;
        dErrordt = (error - errorOld) / delta_t;
        dErrordtFilt = dErrordt * alpha + dErrordtFilt_old * (1 - alpha);
        V = Kp * error + Kd * dErrordtFilt + Ki * integralError;

        dErrordtFilt_old = dErrordtFilt;
        errorOld = error;
        t_old = t;

        V = constrain(V, -10., 10.); // motor saturation
        if (t > StepTime)
        {
            V = 0;
        }
        motor_encoder.set_speed(400 * V / 10);
    }
}

void setup()
{
    Serial.begin(9600);
    motor_encoder.set_speed(200);
    motor_encoder.turn_on();
}

void loop()
{
    Serial.println(motor_encoder.get_pos());
    // pid();
}