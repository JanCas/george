#ifndef CE506111_D7C2_4F9A_8BBB_A35244951C3F
#define CE506111_D7C2_4F9A_8BBB_A35244951C3F

#include <Arduino.h>

enum COLORS{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BROWN,
    ORANGE,
    NOT_A_COLOR
};

class ColorSensor{

    public:
         
        ColorSensor(int red_pin, int green_pin, int blue_pin, int analogPin);
        ~ColorSensor();

        COLORS get_color();
        void calibrate();
        String color_to_string(COLORS color);

    private:
     
        void turn_red();
        void turn_blue();
        void turn_green();
        
        bool is_red(int r, int g, int b);
        bool is_green(int r, int g, int b);
        bool is_blue(int r, int g, int b);
        bool is_brown(int r, int g, int b);
        bool is_yellow(int r, int g, int b);
        bool is_orange(int r, int g, int b); 

        /**
         * @brief populates the rgb_arr
         * 
         */
        void sense();

        void turn_off();

        int red_pin, blue_pin, green_pin, analogPin;
        int delayTime = 20; // ms
        int rgb_arr[3];


};

#endif /* CE506111_D7C2_4F9A_8BBB_A35244951C3F */
