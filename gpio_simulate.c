#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include "useful_functions.h"
#include "assignment_gpio.h"
#include "const.h"

int main(){
	printf("%d\n",(int)round(calc_cycles(50.0)));
	float speed;
	scanf("%f",&speed);
	printf("%f\n",speed);
	int i = 0.0;
	while(1){
		if(round(calc_cycles(speed)) == i){
			write_gpio_value(WHEEL_SENSOR,'1');
			i=0.0;
		}else{
			write_gpio_value(WHEEL_SENSOR,'0');
			i++;
		}
		printf("%c\n",get_gpio_value(WHEEL_SENSOR));
		mdelay(1000000/CYCLES_SECOND);
	}
}