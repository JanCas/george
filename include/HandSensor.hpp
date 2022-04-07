#ifndef D64DD21F_00E0_4890_B4D8_D0821B2BFBCC
#define D64DD21F_00E0_4890_B4D8_D0821B2BFBCC

#include "Arduino.h"

class HandSensor{

    public:
        HandSensor(int analog_pin, int limit);
        ~HandSensor();

        void init();
        bool is_hand();


    private:

        int limit;
        int analog_pin;

};

#endif /* D64DD21F_00E0_4890_B4D8_D0821B2BFBCC */
