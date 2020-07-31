#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>
#include "useful_functions.h"
#include "assignment_gpio.h"
#include "const.h"

int main(){
	int brake = 0;
	int throttle = 0;
	char action;
	while(1){
		printf("\nAction (b,t): ");
		scanf("%c",&action);
		if(action == 'b'){
			if(get_gpio_value(BRAKE) == '0'){
				write_gpio_value(BRAKE,'1');

			}else{
				write_gpio_value(BRAKE,'0');
			}
		}
		if(action == 't'){
			if(get_gpio_value(THROTTLE_0) == '0'){
				write_gpio_value(THROTTLE_0,'1');

			}else{
				write_gpio_value(THROTTLE_0,'0');
			}
		}
		action = '0';
		mdelay(1000);
	}
}