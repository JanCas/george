#ifndef CE506111_D7C2_4F9A_8BBB_A35244951C3F
#define CE506111_D7C2_4F9A_8BBB_A35244951C3F

enum COLORS{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BROWN,
    ORANGE
};

class ColorSensor{

    public:
         
        ColorSensor();
        ~ColorSensor();

        COLORS sense();

};

#endif /* CE506111_D7C2_4F9A_8BBB_A35244951C3F */
