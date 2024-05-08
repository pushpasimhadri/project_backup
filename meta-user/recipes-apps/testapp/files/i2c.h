/**
 * @file           i2c.h
 *
 * @brief          Header file for I2C Interface
 *
 * @Version        1.0
 *
 * @Author         Capgemini Engineering
 */




/* Header FIles */
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/* Macros */
#define I2C_DEV_PATH "/dev/i2c-1"  /* Path to the I2C device */
#define EEPROM_ADDR 0x50          /* I2C device address */
#define EEPROM_REG_ADDR 0x00        /* Address of eeprom register */
#define DIR_SUCCESS 0x00          /* Success code */
#define FILE_OERROR 0x01          /* Open file error code */ 
#define SLAVE_AERROR 0x02         /* Error code for access slave address */
#define EEPROM_RERROR 0x03          /* Error code for eeprom read */
#define INVALID_EEPROM_ERROR 0x04   /* Error code for invalid eeprom data */
#define EEPROM_WERROR 0x05          /* Error code for eeprom write */
#define DIR_LOG printf         /* Macro for information messages */
#define DIR_ERRLOG printf      /* Macro for error messages */
#define BYTE_LENGTH 1
#define MICROSECOND 1000000
#define EEPROM_DATA_SIZE 2
#define OPEN_SUCCESS 0

/*Function name:
 *    readdata - This function reads the data from the M24C64 EEPROM.
 *
 *Parameters:
 *    None
 *
 *Return Value:
 *    i. If the value is equals to zero, then the functions return successful.
 *    ii. If the value is not zero, then the functions returns with the errror code 
 *
 */
float readdata();

/*Function name:
 * 	i2c_main - This function reads the data from the M24C64 EEPROM.
 *
 * Parameters:
 * 	None
 *
 *ReturnValue:
 *	i. If the value is 0, the function returns successful.
 *      ii. If the value is not zero, then the function return with the error code.
 *
 */
int i2c_main();

