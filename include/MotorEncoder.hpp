#ifndef BADE85DE_23EB_439C_B233_928A4F2E5B39
#define BADE85DE_23EB_439C_B233_928A4F2E5B39

#include "Encoder.h"

class MotorEncoder{

    public:
        MotorEncoder(int ena_pin, int in1_pin, int in2_pin, int encoder_a_pin1, int encoder_a_pin2, int encoder_b_pin1, int encoder_b_pin2);
        ~MotorEncoder();

        /**
         * @brief resets the position of the motor&encoder to 0 degrees
         */
        void reset();
        void turn_on();
        int set_speed(int speed);
        void turn_off();
        void cw();
        void ccw();

        int encoder_a_count();
        int encoder_b_count();

        void write(int pos);


    private:

        int ena_pin;
        int in1_pin;
        int in2_pin;

        int speed;

        // position in degrees
        float position;
        Encoder *encoder_a;
        Encoder *encoder_b;

        int normalize_speed(int speed);

};

#endif /* BADE85DE_23EB_439C_B233_928A4F2E5B39 */
