#define WHEELD 300.0 //wheel diameter in mm
#define MAX_ACCELERATION 1.0 //maximum acceleration in m/s/s
#define CYCLES_SECOND 10.0 // (clock cycles per while loop)
#define TRAM_MASS 40000 // mass of the tram in kg
#define AERO_CONSTANT 5702.0 // (derived from a rough calculation, for kinematic modelling)
#define FRICTION_CONSTANT 0.3 // (approximate speed invariate deceleration)
#define BRAKE_FORCE 5000 // (approximate braking force in Newtons)
#define LDR_CUTOFF_HIGH 800 // time (ms). Any > value will engage headlights
#define LDR_CUTOFF_LOW 400 // time (ms). Any < time will disengate headlights
#define PEDESTRIAN_TIME_DELAY 3000
#define FLASH_LIGHTS_INTERVAL 1000
#define NUM_FLASHES 3
#define THROTTLE_ADC 1 // numer of digital outputs for the throttle
#define RPI_GPIO_LOCATION "gpio/"
#define SIM_GPIO_LOCATION "gpio/"
//GPIO pin definitions
#define LIGHT_SENSOR 26
#define THROTTLE_0 13
#define THROTTLE_1 -1
#define THROTTLE_2 -1
#define THROTTLE_3 -1
#define SEVENSEG_A_0 -1
#define SEVENSEG_A_1 -1
#define SEVENSEG_A_2 -1
#define SEVENSEG_A_3 -1
#define SEVENSEG_B_0 -1
#define SEVENSEG_B_1 -1
#define SEVENSEG_B_2 -1
#define SEVENSEG_B_3 -1
#define BRAKE 19
#define HORN 6
#define HEADLIGHTS 5
#define CABIN_LIGHTS 0
#define MOTION_SENSOR 11
#define WHEEL_SENSOR 9
#define DEADMAN_SWITCH 10