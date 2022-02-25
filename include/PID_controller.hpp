#ifndef E15E517E_2512_4F6E_91F7_1B6D54E65F9F
#define E15E517E_2512_4F6E_91F7_1B6D54E65F9F

#include <Arduino.h>

class PID_controller{
    public:

        PID_controller(double Kp, double Kd, double Ki, double step_time, double step_size, double alpha);
        ~PID_controller();

        double compute(float input, double desired);

    private:

        double t_old;
        double T_interval;
        double Kp, Kd, Ki;
        double error_old, dError_filt_old;
        double step_time;
        double step_size;
        double alpha;
};

#endif /* E15E517E_2512_4F6E_91F7_1B6D54E65F9F */
