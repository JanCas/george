#ifndef E11F7FB5_8CEA_44D4_9EE3_41224012755E
#define E11F7FB5_8CEA_44D4_9EE3_41224012755E

//module_pins
int downstram_pin = 7;
int upstream_pin = 9;

// motor encoder pins
int ena_pin = 12;
int in1_pin = 11;
int in2_pin = 10;
int encoder_1_pin = 2;
int encoder_2_pin = 3;
int gear_ratio = 380;
int encoder_counts = 12;

// color_sensing_pins
int red_pin = 5;
int green_pin = 6;
int blue_pin = 7;
int phototransistor_pin = A0;

// swiveler pins
int swiveler_pin = 8;

// HandSensor
int hand_sensor_pin = A1;
int threshold_hand_sensor = 250;

// Hall Sensor Pin
int hall_sensor_pin = 10;

// MM queue
const uint8_t mm_queue_pins[13] = {22, 36, 24, 38, 26, 40, 28, 42, 30, 44, 32, 46, 34};
int emitter_pin = 48;


// PID config values
double K_p = 3.3;
double K_d = .23;
double K_i = 0;
double alpha = 1;

#endif /* E11F7FB5_8CEA_44D4_9EE3_41224012755E */
