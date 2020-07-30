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
// The trams speed is modelled in the following way:
float k_model(float speed,float throttle,int brake){
    speed = speed/3.6; //convert to SI units
    float ke = 1/2 * TRAM_MASS * speed*speed;
    float a;
    if(throttle > 0.1){
	   a = throttle;	
    }
    else{
	   a = -  1*a_gt_b(speed,0.0)*((AERO_CONSTANT * speed * speed / 400000) + FRICTION_CONSTANT);
    }
    if(brake == 1){
        ke = ke - BRAKE_FORCE * speed * 1/CYCLES_SECOND;
        speed = sqrt(2*ke/TRAM_MASS);
    }
    speed = speed + a/CYCLES_SECOND;
    return max((speed*3.6),0.0);
}

//simulate the 7seg display connected to a 4511 microcontroller
void sevenseg_simulate(char bcd[8]){
    int i = 0;
    int speed = 0;
    int tens = 0;
    int units = 0;
    int power;
    while(i<4){
        power = pow(2,(3-i));
        tens = tens + (bcd[i]-'0')*power;
        i++;
    }
    while(i<8){
        power = pow(2,(3-(i-4)));
        units = units + (bcd[i]-'0')*power;
        i++;
    }
    speed = 10*tens+units;
    printf("Current Speed: %d\n",speed);
}

float calc_speed(int cycles){
    long double time = cycles / CYCLES_SECOND; // get amount of time in seconds
    long double distance = WHEELD * 3.14159265 / 1000;
    float speed_ms = distance/time;
    float speed_kph = speed_ms * 3600 / 1000;
    return speed_kph;
}

// function returns the number of cycles to count for a given speed before the GPIO will change
long double calc_time(float speed){
    speed = speed / 3600 * 1000; // SI speed of the tram
    long double distance = WHEELD * 3.14159265 / 1000; // distance for a full wheel revolution in m
    long double time = distance / speed; // number of seconds for a full wheel revolution
    return time;
}

void sevenseg_print(int speed){
    int units = speed%10;
    int tens = floor(speed - units)/10;
    char bcd[8];
    int i = 0;
    int power;
    while(i < 4){
      power = pow(2,(3-i));
      bcd[i] = (tens/power)+'0';
      tens = tens-(bcd[i]-'0')*power;
      i++;
    }
    while(i<8){
      power = pow(2,(3-(i-4)));
      bcd[i] = (units/power)+'0';
      units = units-(bcd[i]-'0')*power;
      i++;
    }
    printf("\n");
    sevenseg_simulate(bcd);
}
