#include "PID_controller.hpp"


PID_controller::PID_controller(double Kp, double Kd, double Ki, double step_time, double step_size, double alpha) {
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;
    this->step_time = step_time;
    this->step_size = step_size;
    this->alpha = alpha;
}

PID_controller::~PID_controller() {}

double PID_controller::compute(float input, double desired){
    
    unsigned long t = micros() / 1000000.0; // current time

    if (t > t_old + T_interval)
    {
        // Controller code
        double delta_t = t - t_old;
        double error = desired - input;
        double integralError = integralError + error * delta_t;
        double dErrordt = (error - error_old) / delta_t;
        double dErrordtFilt = dErrordt * alpha + dError_filt_old * (1 - alpha);
        double V = Kp * error + Kd * dErrordtFilt + Ki * integralError;

        dError_filt_old = dErrordtFilt;
        error_old = error;
        t_old = t;

        V = constrain(V, -10., 10.); // motor saturation
        if (t > step_time)
        {
            V = 0;
        }
        return (400 * V / 10);
    }
}