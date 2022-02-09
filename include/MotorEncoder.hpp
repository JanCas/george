#ifndef BADE85DE_23EB_439C_B233_928A4F2E5B39
#define BADE85DE_23EB_439C_B233_928A4F2E5B39

class MotorEncoder{

    public:
        MotorEncoder();
        ~MotorEncoder();

        /**
         * @brief resets the position of the motor&encoder to 0 degrees
         */
        void reset();

    private:

        float position;

};

#endif /* BADE85DE_23EB_439C_B233_928A4F2E5B39 */
