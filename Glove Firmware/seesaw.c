#include "seesaw.h"

int init_seesaw(){
	printf("Initializing seesaw...\n");
	int file_i2c;
        char *filename = (char*)"/dev/i2c-1";
        if ((file_i2c = open(filename, O_RDWR)) < 0)
        {
                printf("Failed to open the i2c bus");
                return -1;
        }

        if (ioctl(file_i2c, I2C_SLAVE, SEESAW_ADDR) < 0)
        {
                printf("Failed to acquire bus access and/or talk to slave.\n");
                return -1;
        }
	return file_i2c;
}

int init_gpio(){
	return wiringPiSetup();
}

uint16_t seesawADCRead(int file_i2c, char base, char funct, int size){
	char buffer[2] = {0};
	buffer[0] = base;
	buffer[1] = funct;
	char writeByte = SEESAW_ADDR << 1;
	//write(file_i2c, &writeByte, 1);
	if (write(file_i2c, buffer, SEESAW_WRITE_BYTES) != SEESAW_WRITE_BYTES){
		printf("Failed to write to the i2c bus\n");
		printf("%d\n",errno);
		return -1;
	}

	sleep(ADC_READ_DELAY);

	writeByte = SEESAW_ADDR << 1 | 0x01;
	//write(file_i2c, &writeByte, 1);
	char buf[ADC_READ_BYTES] = {0};
	if (read(file_i2c, buf, size) != size){
		printf("Failed to read from i2c bus\n");
		return -1;
	} else {
		int i;
		int val = 0x00;
		for (i = 0; i < ADC_READ_BYTES; i++){
			val |= buf[i] << (ADC_READ_BYTES - 1 - i)*8;
		}
		return val;
	}

}
