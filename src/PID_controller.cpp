#include "PID_controller.hpp"

PID_controller::PID_controller(double Kp, double Kd, double Ki, double alpha)
{
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;
    this->alpha = alpha;
}

PID_controller::~PID_controller() {}

double PID_controller::compute(float input, double desired, float contraint)
{

    t_ms = micros(); // current time
    t = t_ms / 1000000.0;

    if (t > t_old + T_interval)
    {
        // Controller code
        delta_t = t - t_old;
        error = desired - input;
        integralError = integralError + error * delta_t;
        dErrordt = (error - error_old) / delta_t;
        dErrordtFilt = dErrordt * alpha + dError_filt_old * (1 - alpha);
        V = Kp * error + Kd * dErrordtFilt + Ki * integralError;

        dError_filt_old = dErrordtFilt;
        error_old = error;
        t_old = t;

        V = constrain(V, -255., 255.);

        return V;
    }
    return -9999;
}
