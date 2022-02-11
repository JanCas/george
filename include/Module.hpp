#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764

#include "ColorSensor.hpp"

class Module{

    public:

        enum status{
            RUNNING,
            STOPPED
        };

        Module();
        ~Module();

        void calibrate();
        void stop();

    private:

        status curr_status;

        COLORS target_color; 

};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
