#ifndef AF8594C8_ECCA_4DA7_8AE9_2951502DCF54
#define AF8594C8_ECCA_4DA7_8AE9_2951502DCF54

class Switch{

    public:
        Switch(int pin);
        ~Switch();

        /**
         * @brief 
         * reads the value of the switch
         * @return true if the switch is on
         * @return false if the switch is off
         */
        bool is_on();

    private:
        int pin;

};

#endif /* AF8594C8_ECCA_4DA7_8AE9_2951502DCF54 */
