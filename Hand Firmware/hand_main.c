//pi_glove_main
#include "clientpi.h"
#include "clientpi.c"
#include "seesaw.h"
#include "seesaw.c"
#include "./PIGPIO/pigpio.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PWM_ONE 17
#define PWM_TWO 14
#define PWM_THREE 23
#define PWM_FOUR 7
#define PWM_FIVE 16

#define PWM_RANGE 10000
#define PWM_FREQ  50

#define CHANNEL_0 0x07
#define REFRESH_RATE 10000		//refresh rate in microseconds
#define NUM_DIGITS 4

#define MAX_VAL 900
#define MIN_VAL 500

void updateDigitValues();
void writeDigit(uint8_t,uint16_t);
int socketClientConnect();
int init_gpio();
void PWMinit();
uint16_t * getBuffer();

uint16_t digit [NUM_DIGITS];
int fd;

void PWMinit(){

	gpioInitialise();
	//set ranges
	gpioSetPWMrange(PWM_ONE,PWM_RANGE);
	gpioSetPWMrange(PWM_TWO,PWM_RANGE);
	gpioSetPWMrange(PWM_THREE,PWM_RANGE);
	gpioSetPWMrange(PWM_FOUR,PWM_RANGE);
	gpioSetPWMrange(PWM_FIVE,PWM_RANGE);

	//set frequencies
	gpioSetPWMfrequency(PWM_ONE,PWM_FREQ);
	gpioSetPWMfrequency(PWM_TWO,PWM_FREQ);
	gpioSetPWMfrequency(PWM_THREE,PWM_FREQ);
	gpioSetPWMfrequency(PWM_FOUR,PWM_FREQ);
	gpioSetPWMfrequency(PWM_FIVE,PWM_FREQ);
}

/*
This method is meant to pull values
from the socket buffer that have been
written by the glove.
*/
void updateDigitValues(){
  uint8_t n = 0;
  uint16_t * buffer = getBuffer();
  while(n < NUM_DIGITS){
    digit[n] = buffer[n];
    // printf("Value fetched: %d\n",digit[n]);
    n++;
  }
}

/*
This method writes the value returned by the glove
to it's corresponding robotic hand.
*/
void writeDigit(uint8_t n, uint16_t val){
  switch(n){
    case 0: gpioPWM(PWM_ONE, val);
            // printf("Value written to finger 1: %d\n",val);
            break;
    case 1: gpioPWM(PWM_TWO, val);
            // printf("Value written to finger 2: %d\n",val);
            break;
    case 2: gpioPWM(PWM_THREE, val);
            // printf("Value written to finger 3: %d\n",val);
            break;
    case 3: gpioPWM(PWM_FOUR, val);
            // printf("Value written to finger 4: %d\n",val);
            break;
    default: printf("Failed PWM write.");
  }
}

void main(){

  //connect to server
  socketClientConnect();

	//initialize gpio
  init_gpio();

	//initialize PWM pins
  PWMinit();
  uint16_t actualVal = 0;
  uint8_t n;
  while(1){
    n = 0;
    // printf("Updating Value...\n");
    updateDigitValues();
    while(n < NUM_DIGITS){
      if (digit[n] > 900) digit[n] = 900;
      if (digit[n] < 500) digit[n] = 500;
      digit[n] = (digit[n]-500)*(800/400) + 100;
      writeDigit(n, digit[n]);
      n++;
    }
	printf("Robot 0: %d, Robot 1: %d, Robot 2: %d, Robot 3: %d\n",
			digit[0], digit[1], digit[2], digit[3]);
   usleep(REFRESH_RATE);
  }
}
