#include "const.h"
//GPIO setup/generic functions
void pin_setup(char* pin,char direction);
char get_gpio_value(int pin);
void write_gpio_value(int pin, char value);

//GPIO INPUT functions
char get_wheelsensor(void);
float get_throttle(void);
char get_motionsensor(void);
char get_lightdark(void);

//GPIO output funcitons
void ground_throttle(void);
void unground_throttle(void);
void engage_brakes(void);
void disengage_brakes(void);
void ground_throttle(void);
void unground_throttle(void);
void on_headlights(void);
void off_headlights(void);

//complex functions
void flash_lights();

void pin_setup(char* pin,char direction){
  char buf1[0x100];
   snprintf(buf1, sizeof(buf1), "%sexport",RPI_GPIO_LOCATION);
   FILE *fp1 = fopen(buf1, "w");
   fputs(pin,fp1);
   fclose(fp1);
   char buf[0x100];
   snprintf(buf, sizeof(buf), "%sgpio%s/direction",RPI_GPIO_LOCATION,pin);
   FILE *fp = fopen(buf, "w");
   if(direction == 'i'){
    fputs("in",fp);       
   }else{
    fputs("out",fp);
   }
   fclose(fp);
}

//DEPRECATED function to set up a specific pin (on the RPi we can use a general function)
/*
void pin_setup_6(char direction){
  char buf1[0x100];
   snprintf(buf1, sizeof(buf1), "/sys/class/gpio/export");
   FILE *fp1 = fopen(buf1, "w");
   fputs("6",fp1);
   fclose(fp1);
   char buf[0x100];
   snprintf(buf, sizeof(buf), ("/sys/class/gpio/gpio6/direction"));
   FILE *fp = fopen(buf, "w");
   if(direction == 'i'){
    fputs("in",fp);       
   }else{
    fputs("out",fp);
   }
   fclose(fp);
}
*/

char get_gpio_value(int pin){
  char state = '0';
   if(pin != -1){
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%sgpio%d/value",RPI_GPIO_LOCATION,pin);
    FILE *fp = fopen(buf, "r");
    state = fgetc(fp);
    fclose(fp);
  }else{
    return state;
  }
  return state;
}

void write_gpio_value(int pin, char value){
   char buf[0x100];
   snprintf(buf, sizeof(buf), "%sgpio%d/value", RPI_GPIO_LOCATION, pin);
   FILE *fp = fopen(buf, "w");
   fputc(value,fp);
   fclose(fp);
}


//

char get_wheelsensor(){
    int wheelsensor_pin = get_gpio_value(WHEEL_SENSOR);
    return wheelsensor_pin;
}

char get_motionsensor(){
    char motionsensor_pin = get_gpio_value(MOTION_SENSOR);
    printf("pedestrian detected!\n");
    return motionsensor_pin;
}


void on_headlights(void){
	printf("Headlights On");
}

void off_headlights(void){
	printf("Headlights Off");
}

void flash_lights(){
	printf("flash lights");
}

float get_throttle(){
	char throttle_pin = get_gpio_value(THROTTLE_0);
	return throttle_pin;
}

char get_brake(){
    char brake_pin = get_gpio_value(BRAKE);
    return brake_pin;
}

void ground_throttle(){
    write_gpio_value(DEADMAN_SWITCH,'1');
}

void unground_throttle(){
    write_gpio_value(DEADMAN_SWITCH,'0');
}

void sound_horn(){
    write_gpio_value(HORN,'1');
}

void unsound_horn(){
    write_gpio_value(HORN,'0');
}

void engage_brakes(){
    write_gpio_value(BRAKE,'1');
}

void disengage_brakes(){
    write_gpio_value(BRAKE,'0');
}
