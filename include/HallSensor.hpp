#ifndef EB4DB9D7_17DC_4D2C_AC9E_AD5318680978
#define EB4DB9D7_17DC_4D2C_AC9E_AD5318680978

#include "Arduino.h"

class HallSensor{
    public:
        HallSensor(int pin);
        ~HallSensor();

        bool sense();

    private:

        int pin;
};

#endif /* EB4DB9D7_17DC_4D2C_AC9E_AD5318680978 */
