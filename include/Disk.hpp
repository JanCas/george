#ifndef B700CA3A_13CA_4997_94F8_7ED00388A6DF
#define B700CA3A_13CA_4997_94F8_7ED00388A6DF

#include "MotorEncoder.hpp"

enum disk_position_enum{
    COLLECTION = 0,
    HALL_SENSOR = 72,
    COLOR_SENSOR = 144,
    TRASH = 216,
    LAST = 288,
    END = 360
};

class Disk{

    public:

        Disk(MotorEncoder *motor, int limit_switch_pin);
        ~Disk();

        bool move_to_next();
        void pause();
        void continue_disk();
        void reset_time();
        void drive_to_zero();
        void init();

    private:

        bool move_to(disk_position_enum des_position);
        void update_position(disk_position_enum pos);

        bool running;

        disk_position_enum curr_position;
        disk_position_enum next_position;

        int rotation_num;
        int limit_switch_pin;

        MotorEncoder *motor;

};

#endif /* B700CA3A_13CA_4997_94F8_7ED00388A6DF */
