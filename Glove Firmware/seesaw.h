#ifndef SEESAW_H
#define SEESAW_H

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>				//Needed for I2C port
#include <linux/i2c-dev.h>			//Needed for I2C port
#include <inttypes.h>

#define SEESAW_PWM_BASE 		        0x08
#define SEESAW_PWM_WRITE_FUNC 		  0x01
#define SEESAW_PWM_FREQ_FUNC 		    0x02

#define SEESAW_STATUS_HW_ID 		    0x01
#define SEESAW_STATUS_VERSION 		  0x02
#define SEESAW_STATUS_OPTIONS 		  0x03
#define SEESAW_STATUS_SWRST 		    0x7F

#define SEESAW_TIMER_STATUS 		    0x00
#define SEESAW_TIMER_PWM 		        0x01

#define SEESAW_ADC_STATUS 		      0x00
#define SEESAW_ADC_INTEN 		        0x02
#define SEESAW_ADC_INTENCLR 		    0x03
#define SEESAW_ADC_WINMODE 		      0x04
#define SEESAW_ADC_WINTHRESH 		    0x05
#define SEESAW_ADC_CHANNEL_OFFSET 	0x07
#define SEESAW_ADC_DELAY            1000
#define ADC_READ_DELAY              1000
#define SEESAW_ADC_BASE 0x09

#define SEESAW_ADDR 			          0x49
#define SEESAW_WRITE_BYTES 		      2
#define ADC_READ_BYTES 			        2
#define PWM_WRITE_BYTES 		        2
#define PWM_WRITE_DELAY 		        0.001

#define GPIO_BASE 			            0x01
#define GPIO_DIRSET 			          0x02
#define GPIO_DIRCLR 			          0x03
#define GPIO_SET 			              0x05
#define GPIO_CLR 			              0x06

int init_seesaw();
int init_gpio();
uint16_t seesawADCRead(int file_i2c, char base, char funct, int size);

#endif // SEESAW_H
