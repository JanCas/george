#ifndef BADE85DE_23EB_439C_B233_928A4F2E5B39
#define BADE85DE_23EB_439C_B233_928A4F2E5B39

#include "Encoder.h"

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
        Encoder encoder;

};

#endif /* BADE85DE_23EB_439C_B233_928A4F2E5B39 */
