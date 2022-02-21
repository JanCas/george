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
        MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_a_pin1, int encoder_a_pin2, int encoder_b_pin1, int encoder_b_pin2, int gear_ratio, int count, int pulse_count);
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
        int set_speed(int speed);

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


    private:

        int ena_pin;
        int in1_pin;
        int in2_pin;

        int gear_ratio;
        int count;
        int pulse_count; // would be 4 for a quadrature encoder

        float deg_per_count;

        int speed;

        // position in degrees
        float position;
        Encoder *encoder_a;
        Encoder *encoder_b;

        /**
         * @brief normalizes the speed to make sure it doesnt go above 255 or below 0
         * 
         * @param speed 
         * @return int returns the normalized speed
         */
        int normalize_speed(int speed);

};

#endif /* BADE85DE_23EB_439C_B233_928A4F2E5B39 */
