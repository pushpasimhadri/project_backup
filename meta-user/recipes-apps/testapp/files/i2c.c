/**
 *@file        i2c.c
 *
 *@brief       This file implements to read the values from the temperature TMP422 sensor.
 *
 *@Version     1.0
 *
 *@Author      Capgemini Engineering
 */


#include "i2c.h"
#include <unistd.h>

int i2c_fd;

/*Function name:
 *    readdata - This function reads the data form the M24C64 EEPROM.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *    i. If the value is equals to zero, then the functions return successful.
 *    ii. If the value is not zero, then the functions returns with the errror code
 *
 */
float readdata() 
{
	uint8_t eeprom_buffer[EEPROM_DATA_SIZE];    
	float temperature;

	// write command to select the eeprom register 
	if(write(i2c_fd, (void *)EEPROM_REG_ADDR,BYTE_LENGTH) !=BYTE_LENGTH) 
	{
		DIR_ERRLOG("Failed to set pointer address\n");
		return EEPROM_WERROR;
	}
       	else
		DIR_LOG("ACCESS the EEPROM register successfully\n");

	usleep(MICROSECOND);

	// Read eeprom data
	if (read(i2c_fd, eeprom_buffer, EEPROM_DATA_SIZE) !=EEPROM_DATA_SIZE) 
	{
		DIR_ERRLOG("Failed to read from the I2C bus\n");
		return EEPROM_RERROR;
	}
	else
		DIR_LOG("ACCESS the EEPROM buffer successfully \n");

	return DIR_SUCCESS;
}

/*Function name:
 *      i2c_main - This function reads the data from the M24C64 EEPROM.
 *
 * Parameters:
 *      None
 *
 *ReturnValue:
 *      i. If the value is 0, the function returns successful.
 *      ii. If the value is not zero, then the function return with the error code.
 *
 */
int i2c_main() 
{

	// Open I2C device
	if ((i2c_fd = open(I2C_DEV_PATH, O_RDWR)) < OPEN_SUCCESS) 
	{
		DIR_ERRLOG("Failed to open the I2C bus");
		return FILE_OERROR;
	}
	else
		printf("dev path opened successfully \n");

	// Set I2C device address
	if(ioctl(i2c_fd, I2C_SLAVE_FORCE, EEPROM_ADDR) < OPEN_SUCCESS) 
	{
		DIR_ERRLOG("Failed to acquire bus access and/or talk to slave \n");
		return SLAVE_AERROR;
	}
	else
		DIR_LOG("Access the I2c bus successfully \n");

	//Read data from EEPROM
	//Example: Read 10 bytes starting from address 0x00
	unsigned char buffer[10];
	if(read(i2c_fd, buffer, 10) !=10) {
		perror("Failed to read from the device.");
		exit(1);
	}
	//Display read data
	printf("Data read from EEPROM:\n");
	for(int i=0;i<10;i++) {
		printf("%02x", buffer[i]);
	}
	printf("\n");

	/*Close I2C device */
	close(i2c_fd);

	return DIR_SUCCESS;
}

