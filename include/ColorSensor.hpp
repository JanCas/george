#ifndef CE506111_D7C2_4F9A_8BBB_A35244951C3F
#define CE506111_D7C2_4F9A_8BBB_A35244951C3F

class ColorSensor{

    public:
        
        enum colors{
            RED,
            GREEN,
            BLUE,
            YELLOW
        };
        
        ColorSensor();
        ~ColorSensor();

        colors sense();
        void calibrate();

};

#endif /* CE506111_D7C2_4F9A_8BBB_A35244951C3F */
