#ifndef AF8594C8_ECCA_4DA7_8AE9_2951502DCF54
#define AF8594C8_ECCA_4DA7_8AE9_2951502DCF54

class Button{

    public:
        Button();
        ~Button();

        void read();
        bool state();

    private:

        bool state; // true if pressed false if not

};

#endif /* AF8594C8_ECCA_4DA7_8AE9_2951502DCF54 */
