#ifndef EB4DB9D7_17DC_4D2C_AC9E_AD5318680978
#define EB4DB9D7_17DC_4D2C_AC9E_AD5318680978

class HallSensor{
    public:
        HallSensor();
        ~HallSensor();

        bool sense();
        void calibrate();
};

#endif /* EB4DB9D7_17DC_4D2C_AC9E_AD5318680978 */
