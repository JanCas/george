#ifndef ABF48A6D_8977_4DC9_A6A3_46D2B2E41E90
#define ABF48A6D_8977_4DC9_A6A3_46D2B2E41E90

#include <Arduino.h>
#include "ColorSensor.hpp"

class ConfigParser{
    public:
        ConfigParser(const int adress_pins[], const int sorting_color_pins[], const int queue_size_pins[]);
        ~ConfigParser();

        void init();

        bool read(int adress);
        int get_queue_size();
        COLORS get_color();


    private:

        // these pins must be formatted in descending order -> the most significant bit first and the least significant bit last
        const int *adress_pins;
        const int *sorting_color_pins;
        const int *queue_size_pins;

        COLORS color;
        int queue_size;

        static long int int_from_pins(const int *pins);

};

#endif /* ABF48A6D_8977_4DC9_A6A3_46D2B2E41E90 */
