#ifndef CE02A999_ED27_4E3D_B4EF_A9920CC2AABF
#define CE02A999_ED27_4E3D_B4EF_A9920CC2AABF

template <typename T>
class Sensor{
    public:
        virtual void calibrate();
        virtual T sense();
};

#endif /* CE02A999_ED27_4E3D_B4EF_A9920CC2AABF */
