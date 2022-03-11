#ifndef BD9F70C2_485C_4D44_9E82_7E4C03E7027D
#define BD9F70C2_485C_4D44_9E82_7E4C03E7027D

 #include <QTRSensors.h>
 #include <Arduino.h>

class MMQueue{

    public:
        MMQueue(int max_queue_size, const uint8_t sensor_pins[], int emitter_pin);
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

    private:
        int max_queue_size;
        int num_sensors;
        uint16_t *sensor_values;

        QTRSensors *qtr_sensor;

        int num_mm_in_queue();
};

#endif /* BD9F70C2_485C_4D44_9E82_7E4C03E7027D */
