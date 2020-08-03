#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include "useful_functions.h"
#include "assignment_gpio.h"
#include "const.h"
#include <string.h>

int main(int argc, char* argv[]){
	float initial_speed = 1.0;
	int brake = 1;
	float throttle = 0.0;
    if(argc > 1) 
    {
    	int i;
    	for(i=1;i<(argc);i++){
    		if((argv[i][0] = '-') && (argv[i][1] == 'v')){
				char speedbuff[5];
				memcpy( speedbuff, &argv[i][2], (strlen(argv[i]))-2);
				speedbuff[4] = '\0';
				initial_speed = atof(speedbuff);
				if(initial_speed < 1.0){
					initial_speed = 1.0;
				}
    		}
    		if((argv[i][0] = '-') && (argv[i][1] == 'b')){
				char brakebuff[5];
				memcpy( brakebuff, &argv[i][2], (strlen(argv[i]))-2);
				brakebuff[4] = '\0';
				brake = atoi(brakebuff);
			}
    		if((argv[i][0] = '-') && (argv[i][1] == 't')){
				char throttlebuff[5];
				memcpy( throttlebuff, &argv[i][2], (strlen(argv[i]))-2);
				throttlebuff[4] = '\0';
				throttle = atof(throttlebuff);
    		}
    	}
    }
    printf("Initial Speed:%f\n", initial_speed);
    printf("Brake:%d\n", brake);
    printf("Throttle:%f\n", throttle);
	int i = 0;
	float speed = initial_speed;
	long double implied_time;
	int delay_time;
	while(1){
		throttle = get_throttle();
		brake = get_brake();
		printf("Current Speed: %f\n",speed);
		implied_time = calc_time(speed);
		delay_time = (int)round(1000000*implied_time/60);
		if(i == 0){
			write_gpio_value(WHEEL_SENSOR,'1');
		}else{
			write_gpio_value(WHEEL_SENSOR,'0');
		}
		if(i > 58){
			i = 0;
		}else{
			i++;
		}
		mdelay(delay_time);
		printf("%d\n", delay_time);
		speed = k_model(speed,throttle,brake,delay_time);
	}
}