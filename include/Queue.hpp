#ifndef BD9F70C2_485C_4D44_9E82_7E4C03E7027D
#define BD9F70C2_485C_4D44_9E82_7E4C03E7027D

class Queue{

    public:
        Queue(int max_queue_size);
        ~Queue();

        /**
         * @brief 
         * 
         * checks the queue to count how many m&m's are in the funnel
         * 
         * @return true if the queue is not full
         * @return false if the queue is full
         */
        bool check();

    private:
        int num_mm;
        int max_queue_size;


}

#endif /* BD9F70C2_485C_4D44_9E82_7E4C03E7027D */
