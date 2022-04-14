#ifndef AEDE749B_8240_4CFB_8C20_3850DA287764
#define AEDE749B_8240_4CFB_8C20_3850DA287764

#include "ColorSensor.hpp"
#include "Disk.hpp"
#include "MMQueue.hpp"
#include "HallSensor.hpp"
#include "Swiveler.hpp"
#include <cppQueue.h>
#include "LCD.hpp"
#include "HandSensor.hpp"
#include "ConfigParser.hpp"

struct mm_attr{
    bool metal;
    bool right_color;
};

class Module{

    public:

        Module(COLORS target_color, MMQueue *mm_queue, ColorSensor *color_sensor, HallSensor *hall_sensor, Swiveler *swively, 
                Disk *disk, ConfigParser *ConfigParser, int upstream_io_pin, int downstream_io_pin);
        ~Module();

        /**
         * @brief sets the disk position at the beginning
         */
        void calibrate();

        /**
         * @brief a single step in the Module
         * 
         */
        void step();

        /**
         * @brief initializes the module - must be called in init()
         * 
         */
        void init();

    private:

        bool running;
        bool started;
        bool is_top;

        COLORS target_color;
        COLORS last_color;

        int max_queue_size;

        MMQueue *mm_queue;
        ColorSensor *color_sensor;
        HallSensor *hall_sensor;
        Swiveler *swively;
        Disk *disk;
        cppQueue *mm_command_queue;
        HandSensor *hand_sensor;
        MotorEncoder *hopper_motor;
        LCD *lcd;
        ConfigParser *config_parser;

        // intermodular communication
        int upstream_io_pin;
        int downstream_io_pin;

        // LED communication
        int power_led;
        int sorting_active_led;
        int sorting_paused_led;
        int sorting_disabled_led;

        // button_pins
        int e_stop_pin;
        int start_stop_button_pin;

        // tracking sorted mm's
        int num_sorted;
        int num_unsorted;
        int num_contaminants;

        /**
         * @brief senses the color of an mm
         */
        void sense_color();

        /**
         * @brief senses for metal at the hall effect sensor
         */
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
        bool e_stop_activated();

        /**
         * @brief sends message to upstream module to pause
         */
        void send_upstream_pause();

        /**
         * @brief tells the upstream module to continue
         */
        void send_upstream_continue();

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
        COLORS check_mm();

        /**
         * @brief sends the swiveler to the correct position based on the mm
         * 
         */
        void move_swiveler_and_update_counts(const mm_attr &mm_at_swiveler);

        /**
         * @brief didplays the top row on the LCD display - this shows the queue and counts
         * 
         * @param queue_size 
         */
        void display_top_row(int queue_size);

        /**
         * @brief displays the bottom row on the LCD which shows the color
         * !! warning this is a slow command !!
         * 
         * @param color 
         */
        void display_bottom_row(COLORS color);

        /**
         * @brief reads the config from the other mega 
         * TODO: still has to be done and tested
         */
        void wait_for_config();

        /**
         * @brief checks if the start_stop_button has been depressed 
         * 
         * @return true if the button is pressed
         * @return false if the button is not pressed
         */
        bool is_start_stop_button();

        /**
         * @brief special case of pause b/c it contains an infinite loop that waits for e_stop to be reset
         * and the button to be pressed
         */
        void e_stop_pause();

};

#endif /* AEDE749B_8240_4CFB_8C20_3850DA287764 */
