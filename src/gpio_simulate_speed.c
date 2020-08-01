#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include "useful_functions.h"
#include "assignment_gpio.h"
#include "const.h"

int main(){
	float speed;
	scanf("%f",&speed);
	long double implied_time = calc_time(speed);
	int delay_time = (int)round(1000000*implied_time/60);
	int i = 0;
	while(1){
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
	}
}