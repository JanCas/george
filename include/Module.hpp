#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764
class Module{

    public:

        enum position{
            COLLECTION,
            HALL_SENSOR,
            COLOR_SENSOR,
            TRASH,
            LAST,
        };

        Module();
        ~Module();

        void move_to(position desired_pos);
        void calibrate();
        void stop();

    private:

        position current_position;

        float position_deg;

};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
