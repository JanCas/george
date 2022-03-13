#ifndef DCA6BEB8_B1EA_4A96_B4A3_75AA2DE2F294
#define DCA6BEB8_B1EA_4A96_B4A3_75AA2DE2F294

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

class LCD{

    public:

        LCD(int width, int height);
        ~LCD();

        void show_number();

        void test();

    private:

        LiquidCrystal_I2C *lcd;
        int width;
        int height;


};

#endif /* DCA6BEB8_B1EA_4A96_B4A3_75AA2DE2F294 */
