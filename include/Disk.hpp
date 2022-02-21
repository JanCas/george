#ifndef B700CA3A_13CA_4997_94F8_7ED00388A6DF
#define B700CA3A_13CA_4997_94F8_7ED00388A6DF

#include "MotorEncoder.hpp"

enum position{
    COLLECTION = 0,
    HALL_SENSOR = 72,
    COLOR_SENSOR = 144,
    TRASH = 216,
    LAST = 288,
};

class Disk{

    public:

        Disk(MotorEncoder *motor);
        ~Disk();

        bool move_to_next();
        void pause(); 

    private:

        void move_to(position des_position);

        bool running;

        position curr_position;
        position next_position;

        float position_deg;

        MotorEncoder *motor;

};

#endif /* B700CA3A_13CA_4997_94F8_7ED00388A6DF */
