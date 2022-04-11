#ifndef BD9F70C2_485C_4D44_9E82_7E4C03E7027D
#define BD9F70C2_485C_4D44_9E82_7E4C03E7027D

 #include <QTRSensors.h>
 #include <Arduino.h>

class MMQueue{

    public:
        MMQueue( const uint8_t sensor_pins[], int emitter_pin);
        ~MMQueue();

        /**
         * @brief 
         * 
         * checks the queue to count how many m&m's are in the funnel
         * 
         * @return true if the queue is not full
         * @return false if the queue is full
         */
        bool is_full();

        double num_mm_in_queue();

        void init();

    private:
        int num_sensors;

        const uint8_t *sensor_pins;
        int emitter_pin;

        uint16_t sensor_values[13];

        QTRSensors *qtr_sensor;

        
};

#endif /* BD9F70C2_485C_4D44_9E82_7E4C03E7027D */
