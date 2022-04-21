#ifndef DC45CCED_39EE_414A_AB23_373242A36EE2
#define DC45CCED_39EE_414A_AB23_373242A36EE2
#ifndef ABA50877_21A9_4849_9011_E1A2FBA4233F
#define ABA50877_21A9_4849_9011_E1A2FBA4233F
#ifndef E11F7FB5_8CEA_44D4_9EE3_41224012755E
#define E11F7FB5_8CEA_44D4_9EE3_41224012755E

//module_pins
int downstram_pin = 0;
int upstream_pin = 22;
int e_stop_pin = 1;
int start_stop_button_pin = 52;
int power_led = 23;
int sorting_active_led = 25;
int sorting_paused_led = 27;
int sorting_disabled_led = 29;
bool is_top = false; // if this is true then we need another motor_encoder

// motor encoder pins
int ena_pin = 12;
int in1_pin = 11;
int in2_pin = 10;
int encoder_1_pin = 2;
int encoder_2_pin = 3;
int gear_ratio = 380;
int encoder_counts = 12;

// motor_encoder HOPPER pins;
int enb_pin;
int in3_pin;
int in4_pin;

// disk pins
int limit_switch_pin = 50;

// color_sensing_pins
int red_pin = 5; // the orange wire
int green_pin = 6; // the green wire
int blue_pin = 7; //  the yellow wire
int phototransistor_pin = A0;

// swiveler pins
int swiveler_pin = 8;

// HandSensor
int hand_sensor_pin = A1;
int threshold_hand_sensor = 300;

// Hall Sensor Pin
int hall_sensor_pin = 10;

// MM queue
const uint8_t mm_queue_pins[13] = {22, 36, 24, 38, 26, 40, 28, 42, 30, 44, 32, 46, 34};
int emitter_pin = 48;


// PID config values
double K_p = 3.2;
double K_d = .23;
double K_i = 0.0;
double alpha = 1;

// module config
int module_adress = 0;
const int adress_pins[] = {41, 39};
const int sorting_color_pins[] = {47,45,43};
const int queue_size_pins[] = {53,51,49};


#endif /* E11F7FB5_8CEA_44D4_9EE3_41224012755E */


#endif /* ABA50877_21A9_4849_9011_E1A2FBA4233F */


#endif /* DC45CCED_39EE_414A_AB23_373242A36EE2 */
