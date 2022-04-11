#ifndef ABF48A6D_8977_4DC9_A6A3_46D2B2E41E90
#define ABF48A6D_8977_4DC9_A6A3_46D2B2E41E90

#include <Arduino.h>
#include "ColorSensor.hpp"

class ConfigParser{
    public:
        ConfigParser(int adress, const int adress_pins[], const int sorting_color_pins[], const int queue_size_pins[]);
        ~ConfigParser();

        void init();

        bool read();
        int get_queue_size();
        COLORS get_color();


    private:

        // these pins must be formatted in descending order -> the most significant bit first and the least significant bit last
        const int *adress_pins;
        const int *sorting_color_pins;
        const int *queue_size_pins;
        int adress;

        COLORS color;
        int queue_size;

        static int int_from_pins(const int *pins, int length);
        static int convert(char *binary_char);

};

#endif /* ABF48A6D_8977_4DC9_A6A3_46D2B2E41E90 */
