#ifndef BADE85DE_23EB_439C_B233_928A4F2E5B39
#define BADE85DE_23EB_439C_B233_928A4F2E5B39

#include "Encoder.h"

class MotorEncoder{

    public:
        /**
        * @brief Construct a new Motor Encoder object
        * 
        * @param ena_pin 
        * @param in1_pin 
        * @param in2_pin 
        * @param encoder_a_pin1 should be interrupt enabled
        * @param encoder_a_pin2 
        * @param encoder_b_pin1 should be interrupt enabled
        * @param encoder_b_pin2 
        */
        MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_pin1, int encoder_pin2, int gear_ratio, int count);
        ~MotorEncoder();

        /**
         * @brief resets the position of the encoder to 0 degrees
         */
        void reset();

        /**
         * @brief turns on the motor to the speed value in the instance variable
         */
        void turn_on();

        /**
         * @brief Sets the speed of the motor
         * 
         * @param speed 
         * @return int -> the speed it was set to (since the speed will be normalized in case of < 0
         *                                          or > 75)
         */
        double set_speed(double speed);

        /**
         * @brief turns off the motor (does not reset the speed variable)
         */
        void turn_off();

        /**
         * @brief sets rotation to cw
         */
        void cw();

        /**
         * @brief sets rotation to ccw 
         */
        void ccw();

        /**
         * @brief Get the position of the motor in degrees
         * @return float position of motor in degrees 
         */
        float get_pos();

        /**
         * @brief drives to a certain position in degrees [0 - 360]
         * 
         * @param degrees to drive to
         * @return true motor is at that position
         * @return false motor is still driving to position
         */
        bool drive_to(int degrees);

        double set_init_speed(double speed);
        void set_pid_values(double Kp, double Kd, double Ki, double alpha);

        void reset_time() {
            t_old = micros() / 1000000.0;
            t_start = t_old;
        }

    private:

        int ena_pin;
        int in1_pin;
        int in2_pin;

        int gear_ratio;
        int count;
        
        bool direction_clockwise;

        float deg_per_count;

        double speed;

        Encoder *encoder;

        /**
         * @brief normalizes the speed to make sure it doesnt go above 255 or below 0
         * 
         * @param speed 
         * @return int returns the normalized speed
         */
        double normalize_speed(double speed);

        void pid(double des);
        
        double t_start;
        double t_old;
        double T_interval = .001;
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
        double pos;
        double old_pos;
};

#endif /* BADE85DE_23EB_439C_B233_928A4F2E5B39 */
