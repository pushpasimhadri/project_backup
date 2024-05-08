/****************************************************************************
 * FileName:    ApplicationDiagnostic.c
 * Author:      Suresh Kalidasan
 * Date:        20141213
 * Description:
 *              To access any register mapped via I/O range or CPU Range.
 *              This can be cross compiled for any arch.
 *              Suresh.Kalidasan@aricent.com for more information.
 * Version:     V0.1 20141213
 *              -Initial version and has limitation.
 **************************************************************************/

/**
 *@file         testapp.c
 *
 *@brief        Menu driven program to implement testing of interfaces.
 *
 *Description   This file contains functions to test interfaces including UART,SPI,QSPI,I2C,DDR4,Ethernet.
 *
 *@version      1.0
 *
 *@Author       Capgemini Engineering
 */

/*Include files*/
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <asm/ioctl.h>
#include "testapp.h"
#include "i2c.h"
#include "uart.h"
#include "ethernet.h"
#include "spi.h"
#include "ddr.h"

/*node path, make sure to run mknod before this*/
#define Driver_path "/dev/ModuleDiagnostic"
#define DELAY_OPERATION (0)

/*Interface struct between driver and application, user configurable*/
struct mem {
	unsigned int operation;
	unsigned int address;
	unsigned int value;
#if DELAY_OPERATION
	unsigned int delay_value;
#endif
};


enum event Menu;
enum Testcases Choice;
uint16_t result;
char ip_address[MAX_IP_LENGTH];

int main() {
	int hFile;
	int result,i;
	struct mem obj_mem;

	//vic_cvbs_interface stApplnDrvIf;

	hFile = open(Driver_path, O_WRONLY);

	if(hFile == -1)
	{
		printf("open failed for %s\n", Driver_path);
		return -1;
	}
	perror("Opening /home/suresh/diagnostic ");

	obj_mem.operation = 0;
	//int choice,sub_choice;
	while (1) {
		printf("*****Entering into Options*****\n");
		printf("1. SDF FPGA PS\n");
		printf("2. SDF FPGA PL\n");
		printf("3. DMB FPGA PS\n");
		printf("4. DAB FPGA PS\n");
		printf("5. DAB FPGA PL\n");
		printf("6. FPGA read/write\n");
		printf("7. QUIT\n");
		printf("Enter the option(1-6):\n");
		scanf("%d", &Menu);

		switch(Menu) {
			case 1:
				printf("Entering into SDF FPGA PS sub_options\n");
				printf("1. UART0\n");
				printf("2. QSPI\n");
				printf("3. SPI1\n");
				printf("4. DDR4\n");
				printf("5. I2C\n");
				printf("6. GEM0 & GEM1\n");
				printf("7. Quit\n");
				printf("Enter the choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case UART_loopback:
						result = uart_main();
						if( result == DIR_SUCCESS)
							DIR_LOG("UART loopback Interface tested successfully.\n");
						else
							DIR_ERRLOG("Failed to test loopback for UART interface. Return error code: %d\n",result);
						break;

					case QSPI_Interface_test:
						printf("2\n");
						break;

					case SPI_Interface_test:
						result=eeprom_main();
						if(result == DIR_SUCCESS)
							DIR_LOG("Read the values from the EEPROM successfully.\n");
						else
							DIR_ERRLOG("Failed to open SPI device.\n");
						break;

					case DDR4_Interface_test:
						DIR_LOG("DDR Interface test started\n");
						result = ddr_main();
						if(result == DIR_SUCCESS)
							DIR_LOG("DDR memory test success\n");
						else
							DIR_LOG("DDR memory test failed\n");
						break;

					case I2C_Interface_test:
						result = i2c_main();
						if( result == DIR_SUCCESS)
							DIR_LOG("Read the data from EEPROM successfully.\n");
						else
							DIR_ERRLOG("Failed to read the data from the EEPROM. Return error code: %d\n", result);
						break;

					case RGMII_loopback:
						printf("Enter the IP address(self_ping or External_ping) format[xxx.xxx.xxx.xxx]:\n");
						scanf("%s", ip_address);
						struct sockaddr_in stSocadd;
						if(inet_pton(AF_INET, ip_address, &stSocadd.sin_addr) == 1)
						{
							result = ethernet_main(ip_address);
							if (result == PING_SUCCESS)
								DIR_LOG("GEM loopback Interface tested successfully.\n");
							else
								DIR_ERRLOG("Failed to test loopback for GEM Interface. Return error code: %d\n", result);
						}
						else
						{
							printf("Invalid IP address format");
						}
						break;

					case Quit:
						printf("Exiting...\n");
						exit(0);
						break;

					default:
						printf("Invalid choice\n");
						break;
				}
				break;

			case 2:
				printf("Entering into SDF FPGA PL sub_options\n");
				printf("A. AFDX IP CORE\n");
				printf("B. Quit\n");
				printf("Enter your choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case AFDX_IP_CORE_test:
						printf("7\n");
						break;
					case Quit:
						printf("Exiting...\n");
						exit(0);
						break;
					default:
						printf("Invalid choice\n");
						break;
				}
				break;
			case 3:
				printf("Entering into the DMB FPGA PS sub_options\n");
				printf("A. UART\n");
				printf("B. QSPI\n");
				printf("C. SPI1\n");
				printf("D. DDR4\n");
				printf("E. I2C\n");
				printf("F. GEM1\n");
				printf("G. PCIe x2 ROOT COMPLEXT\n");
				printf("H. Quit\n");
				printf("Enter your sub_choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case UART_loopback:
						printf("8\n");
						break;
					case QSPI_Interface_test:
						printf("9\n");
						break;
					case SPI_Interface_test:
						printf("10\n");
						break;
					case DDR4_Interface_test:
						printf("11\n");
						break;
					case I2C_Interface_test:
						printf("12\n");
						break;
					case RGMII_loopback:
						printf("13\n");
						break;
					case PCIe_x2_ROOT_COMPLEXT_test:
						printf("14\n");;
						break;
					case Quit:
						printf("Exiting...\n");
						exit(0);
						break;
					default:
						printf("Invalid choice\n");
						break;
				}
				break;
			case 4:
				printf("Entering into the DAB FPGA PS sub_options\n");
				printf("A. UART\n");
				printf("B. QSPI\n");
				printf("C. SPI1\n");
				printf("D. DDR4\n");
				printf("E. I2C\n");
				printf("F. GEM0\n");
				printf("G. GEM1\n");
				printf("H. GEM2\n");
				printf("I. Quit");
				printf("Enter your sub_choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case UART_loopback:
						printf("15\n");
						break;
					case QSPI_Interface_test:
						printf("16\n");;
						break;
					case SPI_Interface_test:
						printf("17\n");
						break;
					case DDR4_Interface_test:
						printf("18\n");
						break;
					case I2C_Interface_test:
						printf("19\n");
						break;
					case GMII_loopback:
						printf("20\n");
						break;
					case RGMII_loopback:
						printf("21\n");
						break;
					case SGMII_loopback:
						printf("22\n");
						break;
					case Quit:
						printf("Exiting...\n");
						exit(0);
						break;
					default:
						printf("Invalid choice\n");
						break;
				}
				break;
			case 5:
				printf("Entering into the DAB FPGA PL sub_options\n");
				printf("A. MES IP CORE\n");
				printf("B. Quit\n");
				printf("Enter your sub_choice: ");
				scanf("%d", &Choice);
				switch(Choice) {
					case MES_IP_CORE_test:
						printf("24\n");
						break;
					case Quit:
						printf("Exiting...\n");
						exit(0);
						break;
				}
				break;
			case 6:
				{
					printf("Entering into FPGA read/write\n");
					printf("1. 8 BIT Read\n");
					printf("2. 16 BIT Read\n");
					printf("3. 32 BIT Read\n");
					printf("4. 8 BIT Write\n");
					printf("5. 16 BIT Write\n");
					printf("6. 32 BIT Write\n");
					printf(" Pass Operation Code \n");
					scanf("%d", &obj_mem.operation);

					switch(obj_mem.operation) {

						case 1:
							printf(" 8 bit Read Selected \n");
							printf(" Pass Address \n");
							scanf("%x", &obj_mem.address);
							break;
						case 2:
							printf(" 16 bit Read Selected \n");
							printf(" Pass Address \n");
							scanf("%x", &obj_mem.address);
							break;
						case 3:
							printf(" 32 bit Read Selected \n");
							printf(" Pass Address \n");
							scanf("%x", &obj_mem.address);
							break;
						case 4:
							printf(" 8 bit Write Selected \n");
							printf(" Pass Address \n");
							scanf("%x", &obj_mem.address);
							printf(" Pass Value \n");
							scanf("%x", &obj_mem.value);
							break;
						case 5:
							printf(" 16 bit Write Selected \n");
							printf(" Pass Address \n");
							scanf("%x", &obj_mem.address);
							printf(" Pass Value \n");
							scanf("%x", &obj_mem.value);
							break;
						case 6:
							printf(" 32 bit Write Selected \n");
							printf(" Pass Address \n");
							scanf("%x", &obj_mem.address);
							printf(" Pass Value \n");
							scanf("%x", &obj_mem.value);
							break;
						default:
							printf(" Wrong entry, pls try example if you want to do \n");
							printf(" 16 bit word read, your input should be 14 \n");
							printf(" Here (1) for Read & (4) for Word \n");

					}
#if DELAY_OPERATION
					printf(" Enter delay value (in ms) default value - 0 \n");
					scanf("%x", &obj_mem.delay_value);
#endif
					result = ioctl(hFile,0,&obj_mem);
					if( (obj_mem.operation == 1) || (obj_mem.operation == 2) || (obj_mem.operation == 3) )
					{
						printf("INFO:\t Register: %X Value: %X\n", obj_mem.address, result);
					}
				}
				break;
			case 7:
				printf("Exit\n");
				close(hFile);
				exit(0);
				break;

		}
	}
	return 0;
}









