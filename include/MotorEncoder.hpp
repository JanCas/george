#ifndef BADE85DE_23EB_439C_B233_928A4F2E5B39
#define BADE85DE_23EB_439C_B233_928A4F2E5B39

#include "Encoder.h"
#include "PID_controller.hpp"

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
        MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_pin1, int encoder_pin2, int gear_ratio, int count, PID_controller *pid_controller);
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

        void set_speed_constraint(int speed);

    private:

        int ena_pin;
        int in1_pin;
        int in2_pin;

        int gear_ratio;
        int count;

        bool direction_clockwise;

        float deg_per_count;

        double speed;
        int speed_constraint;

        Encoder *encoder;
        PID_controller *pid_controller;

        /**
         * @brief normalizes the speed to make sure it doesnt go above 255 or below 0
         * 
         * @param speed 
         * @return int returns the normalized speed
         */
        double normalize_speed(double speed);


};

#endif /* BADE85DE_23EB_439C_B233_928A4F2E5B39 */
