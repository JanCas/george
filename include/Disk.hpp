#ifndef B700CA3A_13CA_4997_94F8_7ED00388A6DF
#define B700CA3A_13CA_4997_94F8_7ED00388A6DF

#include "MotorEncoder.hpp"

class Disk{

    public:

        enum position{
            COLLECTION,
            HALL_SENSOR,
            COLOR_SENSOR,
            TRASH,
            LAST,
        };

        Disk();
        ~Disk();

        void move_to(position des_position);
        

    private:

        position curr_position;

        float position_deg;

        MotorEncoder *motor;

};

#endif /* B700CA3A_13CA_4997_94F8_7ED00388A6DF */