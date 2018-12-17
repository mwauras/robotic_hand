#include "seesaw.h"
#include "seesaw.c"
// #include "serverpi.h"
#include "serverpi.c"
#include <string.h>

#define SELECT_A 			4
#define SELECT_B 			5
#define SELECT_C 			6
#define CHANNEL_0 		0x07				//The ADC pin used to read analog values
#define REFRESH_RATE  10000		//refresh rate in microseconds
#define NUM_DIGITS 		4

void setSelect(int flex){
	if (flex == 0){
		digitalWrite(SELECT_A,0);
        	digitalWrite(SELECT_B,0);
        	digitalWrite(SELECT_C,1);
	} else if (flex == 1){
		digitalWrite(SELECT_A,0);
        	digitalWrite(SELECT_B,1);
        	digitalWrite(SELECT_C,0);
	} else if (flex == 2){
		digitalWrite(SELECT_A,1);
                digitalWrite(SELECT_B,0);
                digitalWrite(SELECT_C,0);
	} else if (flex == 3){
		digitalWrite(SELECT_A,1);
                digitalWrite(SELECT_B,1);
                digitalWrite(SELECT_C,0);
	} else if (flex == 4){
		digitalWrite(SELECT_A,1);
                digitalWrite(SELECT_B,1);
                digitalWrite(SELECT_C,1);
	} else {
		printf("No flex sensor with index %d\n", flex);
	}
}

void main(){

	int fd = wiringPiI2CSetup(SEESAW_ADDR);
	init_gpio();
	uint8_t val = 0x00;
	int sel = 0;
	uint16_t values[NUM_DIGITS] = {0};

	pinMode(SELECT_A,OUTPUT);
	pinMode(SELECT_B,OUTPUT);
	pinMode(SELECT_C,OUTPUT);

	socketServerConnect();

	while(1){
		for (sel = 0; sel < NUM_DIGITS; sel++){
			setSelect(sel);
			usleep(ADC_READ_DELAY);
			values[sel] = seesawADCRead(fd,SEESAW_ADC_BASE,CHANNEL_0,2);
		}
		printf("Flex 0: %d, Flex 1: %d, Flex 2: %d, Flex 3: %d\n",
			values[0], values[1], values[2], values[3]);

		//flush buffer
		fflush(stdout);
		//write values to socket file descriptor
    n = write(newsockfd,&values,sizeof(values));
    if (n < 0)
         error("ERROR writing to socket");
		 //flush buffer
 		fflush(stdout);
		//printf("Value fetched: %d\n",seesawADCRead(fd,0x09,0x07,2));
		usleep(REFRESH_RATE);
	}
}
