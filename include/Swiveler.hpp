#ifndef B88F8F98_8AEF_4956_A98B_C2E3A697A545
#define B88F8F98_8AEF_4956_A98B_C2E3A697A545

#include <Servo.h>


enum position_enum{
    CLOSED,
    BUCKET,
    NEXT_MODULE,
};

class Swiveler{
    public:

        Swiveler(int servo_pin);
        ~Swiveler();

        void move_to(position_enum desired_pos);
        void init();

    private:
        int pin_num;
        position_enum position;
        Servo *servo;
        
};

#endif /* B88F8F98_8AEF_4956_A98B_C2E3A697A545 */
