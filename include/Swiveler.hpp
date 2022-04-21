#ifndef B88F8F98_8AEF_4956_A98B_C2E3A697A545
#define B88F8F98_8AEF_4956_A98B_C2E3A697A545

#include <Servo.h>


enum swiveler_position_enum{
    CLOSED = 80,
    BUCKET = 0,
    NEXT_MODULE = 25,
};

class Swiveler{
    public:

        Swiveler(int servo_pin);
        ~Swiveler();

        void move_to(swiveler_position_enum desired_pos);
        void init();
        void move_to_degree(int degree);

    private:
        int pin_num;
        swiveler_position_enum position;
        Servo *servo;
        
};

#endif /* B88F8F98_8AEF_4956_A98B_C2E3A697A545 */
