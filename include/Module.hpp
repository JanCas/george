#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764

#include "ColorSensor.hpp"
#include "Disk.hpp"
#include "MMQueue.hpp"
#include "HallSensor.hpp"
#include "Swiveler.hpp"
#include <cppQueue.h>
#include "LCD.hpp"

struct mm_attr{
    bool metal;
    bool right_color;
};

class Module{

    public:

        Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, 
                Disk *disk, MotorEncoder *shaker_motor, int upstream_io_pin, int downstream_io_pin);
        Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, Swiveler *swively, Disk *disk);
        ~Module();

        void calibrate();
        void step();
        void init();

    private:

        bool running;

        COLORS target_color;
        int max_queue_size;

        MMQueue *mm_queue;
        ColorSensor *color_sensor;
        HallSensor *hall_sensor;
        Swiveler *swively;
        Disk *disk;
        cppQueue *mm_command_queue;
        MotorEncoder *shaker_motor;
        LCD *lcd;

        int upstream_io_pin;
        int downstream_io_pin;

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
         * @brief if the module is paused then it continues
         */
        void continue_module();

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
        void move_swiveler(const mm_attr &mm_at_swiveler);

        void print_mm(const mm_attr &mm);

        void display_mm_color(COLORS color);

        void display_queue_size(int queue_size);
};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
