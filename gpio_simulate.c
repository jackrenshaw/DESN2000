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
	printf("%Lf\n%d\n", implied_time,delay_time);
	int i = 0;
	while(1){
		printf("%c\n", get_gpio_value(WHEEL_SENSOR));
		if(i < 3){
			write_gpio_value(WHEEL_SENSOR,'1');
		}else{
			write_gpio_value(WHEEL_SENSOR,'0');
		}
		mdelay(delay_time);
		if(i > 60){
			i = 0;
		}else{
			i++;
		}
	}
}