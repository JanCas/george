#ifndef DCA6BEB8_B1EA_4A96_B4A3_75AA2DE2F294
#define DCA6BEB8_B1EA_4A96_B4A3_75AA2DE2F294

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

enum ALIGNMENT_ENUM{
    LEFT,
    CENTER,
    RIGHT
};

class LCD{

    public:

        LCD(int width, int height);
        ~LCD();

        void init();
        void display_message(String message, ALIGNMENT_ENUM alignment, int row);
        void clear_row(int row);
        void clear();

    private:

        void display_left_aligned(String message, int row);
        void display_center_aligned(String message, int row);
        void display_right_aligned(String message, int row);

        LiquidCrystal_I2C *lcd;
        int width;
        int height;


};

#endif /* DCA6BEB8_B1EA_4A96_B4A3_75AA2DE2F294 */
