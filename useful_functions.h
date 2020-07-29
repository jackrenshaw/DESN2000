#include "const.h"
//general functions
void mdelay(int milli_seconds);
int a_gt_b(float a,float b);
float max(float a,float b);

float k_model(float speed,float throttle,int brake);
void sevenseg_simulate(char bcd[8]);
float calc_speed(int cycles);


void mdelay(int milli_seconds) 
{ 
    // Converting time into milli_seconds 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) ; 
} 

int a_gt_b(float a,float b){ // function returns 1 if a is greater than b 0 otherwise
    if(a > b){
	return 1;
    }else{
	return 0;
    }
}

float max(float a,float b){ // function returns the max value of two inputs
    if(a>b){
	return a;
    }else{
	return b;
    }
}

// models the speed of the tram based on current speed, throttle power and brake (boolean)
// function needs to be called every clock cycle to be accurate
// # defined values for kinetic coefficients are used
float k_model(float speed,float throttle,int brake){
    speed = speed/3.6; //convert to SI units
    float a;
    if(throttle > 0.1){
	   a = throttle;	
    }
    else{
	   a = -  1*a_gt_b(speed,0.0)*((AERO_CONSTANT * speed * speed / 400000) + FRICTION_CONSTANT);
    }
    a = a - BRAKE_DECELERATION*brake;
    speed = speed + a/CYCLES_SECOND;
    return max((speed*3.6),0.0);
}

//simulate the 7seg display connected to a 4511 microcontroller
void sevenseg_simulate(char bcd[8]){

}

float calc_speed(int cycles){
    long double time = cycles / CYCLES_SECOND;
    long double distance = WHEELD * 3.14159265 / 1000;
    float speed_ms = distance/time;
    float speed_kph = speed_ms / 3600 * 1000;
    return speed_kph;
}

void sevenseg_print(int speed){
    int units = speed%10;
    int tens = floor(speed - units);
    char bcd[8];
    int i = 0;
    while(i < 4){
      bcd[i] = tens/pow(2,(3-i))+'0';
      tens = tens-bcd[i];
      i++;
    }
    while(i<8){
      bcd[i] = units/pow(2,(3-(i-4)))+'0';
      units = units-bcd[i];
      i++;
    }
    sevenseg_simulate(bcd);
}
