#ifndef B88F8F98_8AEF_4956_A98B_C2E3A697A545
#define B88F8F98_8AEF_4956_A98B_C2E3A697A545



class Swiveler{
    public:
        
        enum position_enum{
            CLOSED,
            BUCKET,
            NEXT_MODULE,
        };

        Swiveler();
        ~Swiveler();

        void move_to(position_enum desired_pos);

    private:
        position_enum position;
        
};

#endif /* B88F8F98_8AEF_4956_A98B_C2E3A697A545 */
