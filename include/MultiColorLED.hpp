#ifndef A580BEFC_5232_4B7E_8FE4_2D2311CE7450
#define A580BEFC_5232_4B7E_8FE4_2D2311CE7450

enum LEDcolors{
    red,
    green,
    blue
};

class MultiColorLED{

    public:

        MultiColorLED();
        ~MultiColorLED();

        void turn_on();
        void turn_off();

    private:

        LEDcolors target_color;

};

#endif /* A580BEFC_5232_4B7E_8FE4_2D2311CE7450 */
