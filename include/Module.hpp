#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764

#include "ColorSensor.hpp"
#include "Disk.hpp"
#include "MMQueue.hpp"
#include "HallSensor.hpp"
#include "Swiveler.hpp"
#include "Dashboard.hpp"

class Module{

    public:

        enum status{
            RUNNING,
            STOPPED
        };

        Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, DashBoard *dash_board);
        ~Module();

        void calibrate();
        void stop();
        void step();

    private:

        status curr_status;

        COLORS target_color; 
        MMQueue *mm_queue;
        ColorSensor *color_sensor;
        HallSensor *hall_sensor;
        Swiveler *swively;
        DashBoard *dash_board;

};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
