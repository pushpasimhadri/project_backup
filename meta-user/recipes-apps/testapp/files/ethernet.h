/**
 * @file     ethernet.h
 *
 * @brief    Header file for Ethernet loopback test.
 *
 * @Version  1.0
 *
 * @Author   Capgemini Engineering
 */

/* Header FIles */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Macros */
#define MAX_IP_LENGTH 15 // Maximum length of an IPv4 address (including null terminator)
#define DIR_SUCCESS 0x00          /* Success code */
#define DIR_ERRLOG printf      /* Macro for error messages */
#define EXPECTED_ARGC 2        //expected number of command-line arguments 
#define IP_ADDRESS_ARG_INDEX 0 //Index of the command-line argument
#define COMMAND_SIZE 100       // Size of the command buffer
#define LINE_SIZE 256          // Size of the line buffer
#define VALID_IP 1             // Indicates a valid IP address
#define INVALID_IP 0          // Indicates an invalid IP address
#define DIR_LOG printf         /* Macro for information messages */
#define DIR_ERRLOG printf      /* Macro for error messages */
#define ERROR_STATUS -1
#define PROG_NAME_INDEX 0

/* Function name
 *      ethernet_main - This function perform loopback test for ethernet interface.
 *
 * parameters
 *      The number of command-line arguments.
 *      The array of command-line arguments.
 *
 * Return value
 *      i. If the value is 0, the function returns successful.
 *      ii. If the value is not zero, then the function return with the error code.
 */

int ethernet_main(char *argv);

