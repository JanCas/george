#ifndef E15E517E_2512_4F6E_91F7_1B6D54E65F9F
#define E15E517E_2512_4F6E_91F7_1B6D54E65F9F

#include <Arduino.h>

class PID_controller{
    public:

        PID_controller(double Kp, double Kd, double Ki, double alpha);
        ~PID_controller();

        double compute(float input, double desired, float contraint);


    private:

        double t_old;
        double T_interval = .01;
        double Kp, Kd, Ki;
        double error_old, dError_filt_old;
        double delta_t;
        double error;
        double integralError;
        double dErrordt;
        double dErrordtFilt;
        double V;
        unsigned long t_ms;
        double t;
        double alpha;
        double step_time;
};

#endif /* E15E517E_2512_4F6E_91F7_1B6D54E65F9F */
