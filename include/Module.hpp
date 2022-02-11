#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764

#include "ColorSensor.hpp"

class Module{

    public:

        enum position{
            COLLECTION,
            HALL_SENSOR,
            COLOR_SENSOR,
            TRASH,
            LAST,
        };

        enum status{
            RUNNING,
            STOPPED
        };

        Module();
        ~Module();

        void move_to(position desired_pos);
        void calibrate();
        void stop();

    private:

        position current_position;
        status curr_status;

        float position_deg;

        ColorSensor.colors target_color;

};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
