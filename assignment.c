#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include "useful_functions.h"
#include "assignment_gpio.h"
#include "const.h"

// function takes a integer speed in kph(NOTE: speed is treated as a floating point in most operations)
// and prints the speed to a 7seg display via a 4511 BCD to 7seg converter
// 

/*int main(){
printf("  ____    _____   ____    _   _   ____     ___     ___     ___  \n");
printf(" |  _ \\  | ____| / ___|  | \\ | | |___ \\   / _ \\   / _ \\   / _ \\ \n");
printf(" | | | | |  _|   \\___ \\  |  \\| |   __) | | | | | | | | | | | | |\n");
printf(" | |_| | | |___   ___) | | |\\  |  / __/  | |_| | | |_| | | |_| |\n");
printf(" |____/  |_____| |____/  |_| \\_| |_____|  \\___/   \\___/   \\___/ \n");
printf("\n");
printf("     _                  _                                              _   \n");
printf("    / \\     ___   ___  (_)   __ _   _ __    _ __ ___     ___   _ __   | |_ \n");
printf("   / _ \\   / __| / __| | |  / _` | | '_ \\  | '_ ` _ \\   / _ \\ | '_ \\  | __|\n");
printf("  / ___ \\  \\__ \\ \\__ \\ | | | (_| | | | | | | | | | | | |  __/ | | | | | |_ \n");
printf(" /_/   \\_\\ |___/ |___/ |_|  \\__, | |_| |_| |_| |_| |_|  \\___| |_| |_|  \\__|\n");
printf("---------------------------------------------------------------------------\n");
printf("Authors:\n");
printf(" - Jack Renshaw\n");
printf(" - Ayden Young\n");
printf(" - Sashan De Silva\n");
printf("testing");         
printf("testing again");                                                    
	
	pin_setup_26('i');
	pin_setup_19('o');
	printf("pass");
	char ws_t = '1'; //wheel sensor NOW
	char ws_tm = '1'; //wheel sensor on prior clock cycle
	char throttle = '0'; // default to no throttle
    	clock_t start_time = clock();
	sevenseg_simulate('1','0','0','0','0','0','0','1');
	while(1){
	   ws_t = get_wheelsensor();
	   throttle = get_throttle();
	   printf("%c:%c\n",ws_t,throttle);
	   if((ws_t == '1') && (ws_tm = '0')){ // falling edge of the hall sensor
	    clock_t now_time = clock();	
	    int speed = (int) calc_speed((float)(now_time-start_time));
	    printf("speed:%d",speed); 	
	   };
	   mdelay(1000);
	}
	return 0;
}*/

/*int main(){
    pin_setup_26('i'); // throttle
    pin_setup_19('i'); // throttle
    pin_setup_13('i'); // brake
    pin_setup_6('o'); // brake grounding transistor base
    float throttle;
    int brake,throttle_ground_var,wheel_sensor_current_cycle;
    float speed = 50.0;
    int cycles_since_trigger = CYCLES_SECOND;
    int wheel_sensor_last_cycle = '0';
    while(1){
	wheel_sensor_current_cycle = get_wheelsensor();
	printf("%c\n",wheel_sensor_current_cycle);
	if((wheel_sensor_current_cycle = '0') && (wheel_sensor_last_cycle == '1')){
	    printf("measured speed: %f\n",calc_speed(cycles_since_trigger));
	    cycles_since_trigger = 0;
	}else{
	 cycles_since_trigger++;   
	}
	wheel_sensor_last_cycle = wheel_sensor_current_cycle;
	if(throttle_ground_var == 0){
	    throttle = get_throttle();
	}else{
	    throttle = 0.0;
	}
	int brake = (get_brake());
	speed = k_model(speed,throttle,brake);
	sevenseg_print((int)speed);
	if(speed > 50.0){
	    throttle_ground_var = 1;
	    throttle_ground(1);
	}else{
	    throttle_ground_var = 0;
	    throttle_ground(0);
	}
	mdelay(1000000/CYCLES_SECOND);
    }
    return 0;
}*/

int main(){
  printf("  ____    _____   ____    _   _   ____     ___     ___     ___  \n");
  printf(" |  _ \\  | ____| / ___|  | \\ | | |___ \\   / _ \\   / _ \\   / _ \\ \n");
  printf(" | | | | |  _|   \\___ \\  |  \\| |   __) | | | | | | | | | | | | |\n");
  printf(" | |_| | | |___   ___) | | |\\  |  / __/  | |_| | | |_| | | |_| |\n");
  printf(" |____/  |_____| |____/  |_| \\_| |_____|  \\___/   \\___/   \\___/ \n");
  printf("\n");
  printf("     _                  _                                              _   \n");
  printf("    / \\     ___   ___  (_)   __ _   _ __    _ __ ___     ___   _ __   | |_ \n");
  printf("   / _ \\   / __| / __| | |  / _` | | '_ \\  | '_ ` _ \\   / _ \\ | '_ \\  | __|\n");
  printf("  / ___ \\  \\__ \\ \\__ \\ | | | (_| | | | | | | | | | | | |  __/ | | | | | |_ \n");
  printf(" /_/   \\_\\ |___/ |___/ |_|  \\__, | |_| |_| |_| |_| |_|  \\___| |_| |_|  \\__|\n");
  printf("---------------------------------------------------------------------------\n");
  printf("Authors:\n");
  printf(" - Jack Renshaw\n");
  printf(" - Ayden Young\n");
  printf(" - Sashan De Silva\n");
  int prev = 0;
  int curr = 0;
  int wheel_cycles = 0;
  clock_t start_time = clock();
  clock_t end_time;
  printf("stopping distance 50kph: %f\n",stopping_distance(20.0,0.0));
  printf("stopping distance with brake 50kph: %f\n",stopping_distance(20.0,1.0));
  long double delay;
  float curr_speed;
  float avg_speed;
  int i =0;
  float speed_vals[5] = {0,0,0,0,0};
  while(1){
  	curr = get_gpio_value(WHEEL_SENSOR);
  	if((prev == '1') && (curr == '0')){
   		end_time = clock(); 
   		delay = (float)(end_time-start_time)/(float)CLOCKS_PER_SEC;
  		curr_speed = calc_speed(delay);
      i = 4;
      while(i > 0){
        speed_vals[i] = speed_vals[(i-1)];
        i--;
      }
      speed_vals[0] = curr_speed;
      avg_speed = smooth_speed(speed_vals);
      if(avg_speed > MAX_SPEED){
        ground_throttle();
      }
      printf("Average Speed %f\n",avg_speed);
  		start_time = end_time; 
  	}
  	prev = curr;
  	mdelay(1000);
  	i++;
  }
}
