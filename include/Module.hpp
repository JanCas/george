#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764

#include "ColorSensor.hpp"
#include "Disk.hpp"
#include "MMQueue.hpp"
#include "HallSensor.hpp"
#include "Swiveler.hpp"
#include "Dashboard.hpp"
#include <cppQueue.h>

struct mm_attr{
    bool metal;
    bool right_color;
};

class Module{

    public:

        Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, DashBoard *dash_board, Disk *disk);
        ~Module();

        void calibrate();
        void step();
        void init();

    private:

        bool running;

        COLORS target_color; 
        MMQueue *mm_queue;
        ColorSensor *color_sensor;
        HallSensor *hall_sensor;
        Swiveler *swively;
        DashBoard *dash_board;
        Disk *disk;
        cppQueue *mm_command_queue;

        void sense_color();
        void sense_metal();

        /**
         * @brief checks if the downstream message is to stop the arduino
         * @return true downstream queue is full
         * @return false downstream queue is not full
         */
        bool check_downstream();

        /**
         * @brief pauses the module
         */
        void pause();

        /**
         * @brief reads the e-stop button and makes sure the arduino knows whats going on 
         * @return true e stop button is on
         * @return false e stop button is off 
         */
        bool e_stop();

        /**
         * @brief sends message to upstream arduino on wether it should pause or run
         * @param run [in] if true then the upstream arduino will pause, if false the upstream arduino will run
         */
        void send_upstream(bool pause);

        /**
         * @brief is there a hand in the machine
         * 
         * @return true yes there is a hand in the machine
         * @return false no there isnt a hand in the machine
         */
        bool is_hand();

        /**
         * @brief reads the hall sensor and the color position and adds the appropriate things to the queue
         * 
         */
        void check_mm();

        /**
         * @brief sends the swiveler to the correct position based on the mm
         * 
         */
        void move_swiveler(mm_attr mm_at_swiveler);

        void print_mm(mm_attr mm);
};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
