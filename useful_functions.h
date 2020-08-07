#include <math.h>
#include "const.h"

//general functions
void mdelay(int milli_seconds);
int a_gt_b(float a,float b);
float max(float a,float b);

float k_model(float speed,float throttle,float brake);
void sevenseg_simulate(char bcd[8]);
float calc_speed(long double time);
long double calc_time(float speed);
float smooth_speed(float speed[5]);


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



void floattodig(float number){
  float dig_vals[16] = {0.0,0.0625,0.125,0.1875,0.250,0.3125,0.375,0.4375,0.5,0.5625,0.625,0.6875,0.75,0.875,0.9375,1.0};
  int bin_equiv[16][4] = {{0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},{1,0,0,0},{1,0,0,1},{1,0,1,0},{1,0,1,1},{1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1}};
  float min_sep = 1.0;
  int i,digital_equiv;
  for(i=0;i<16;i++){
    if(fabs(number-dig_vals[i]) < min_sep){
      digital_equiv = i;
      min_sep = fabs(number-dig_vals[i]);
    }
  }
  for(i=0;i<4;i++){
    printf("%d ",bin_equiv[digital_equiv][i]);
  }
}

// models the speed of the tram based on current speed, throttle power and brake (boolean)
// function needs to be called every clock cycle to be accurate
// # defined values for kinetic coefficients are used
// The trams speed is modelled in the following way:
float k_model(float speed,float throttle,float brake){
    double nspeed = speed/3.6; //convert to SI units
    float a = 0;
    if(throttle > 0.1){
       nspeed = nspeed + throttle;
    }else{
        nspeed = nspeed - FRICTION_CONSTANT;
        double ke = 0.5 * TRAM_MASS * nspeed*nspeed;
        float distance = nspeed;
        float aero_force = (0.5*AERO_CONSTANT*nspeed*nspeed);
        ke = ke - fabs(aero_force*distance);
        ke = ke - fabs(brake*(BRAKE_FORCE*distance));
        nspeed = sqrt((2*ke)/TRAM_MASS);
    }
    return max((nspeed*3.6),0.1);
}

float stopping_distance(float speed,float brake){
    float distance = 0.0;
    float curr_speed = speed;
    while(curr_speed > 1.0){
        curr_speed = k_model(curr_speed,0.0,brake);
        distance = distance + curr_speed;
    }
    return distance;
}

float min_stopping_brake_force(float speed, float station_distance){
    float i=0.1;
    float st_d = stopping_distance(speed,0.0);
    while((i<1.1) && (st_d>station_distance)){
        st_d = stopping_distance(speed,i);
        i = i+0.1;
    }
    printf("Min braking force is %f\n",i);
    return i;
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

float calc_speed(long double time){
    long double distance = WHEELD * 3.14159265 / 1000;
    float speed_ms = distance/time;
    float speed_kph = speed_ms * 3600 / 1000;
    return speed_kph;
}

// function returns the number of cycles to count for a given speed before the GPIO will change
long double calc_time(float speed){
    float nspeed = speed / 3600 * 1000; // SI speed of the tram
    long double distance = WHEELD * 3.14159265 / 1000; // distance for a full wheel revolution in m
    long double time;
    if(speed > 0.01){
        time = distance / nspeed; // number of seconds for a full wheel revolution
    }else{
        time = 10000.0000;
    }
    return time;
}

float smooth_speed(float speed[5]){
    float avg_speed = 0.0;
    float residuals[5];
    float avg_residual = 0;
    float max_residual = 0;
    int max_residual_index = 0;
    int i;
    i=0;
    while(i<5){
        avg_speed = avg_speed + (5-i)*speed[i]; // 5x0 + 4x1 + 3x2 + 2x3 + 1x4 / 15
        i++;
    }
    avg_speed = avg_speed/15;
    if((speed[0] > 0.0) && (speed[1] > 0.0) && (speed[2] == 0.0) && (speed[3] == 0.0)){
        avg_speed = speed[0];
        speed[1] = speed[0];
        speed[2] = speed[0];
        speed[3] = speed[0];
        speed[4] = speed[0];
    }
    i=0;
    while(i<5){
        residuals[i] = (speed[i] - avg_speed)*(speed[i] - avg_speed);
        avg_residual = avg_residual + residuals[i];
        if(residuals[i] > max_residual){
            max_residual = residuals[i];
            max_residual_index = i;
        }
        i++;
    }
    avg_residual = avg_residual/5;
    if((max_residual > (avg_speed/2)) && (avg_speed != 0.0)){
        speed[max_residual_index] = avg_speed;
        avg_speed = smooth_speed(speed);
    }
    return avg_speed;
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
    sevenseg_simulate(bcd);
}
