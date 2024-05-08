/**
 * @file        ethernet.c
 *
 * @brief       This file implements loopback test for Ethernet interface.
 *
 * @Version     1.0
 *
 * @Author      Capgemini Engineering
 */


#include "ethernet.h"

/* Function name:
 * 	ip_is_assigned - Check if an IP address is assigned to any interface.
 *
 * Parameters:
 * 	ip_address
 *
 * Return value:
 * 	Returns DIR_SUCCESS if the IP address is assigned to any interface, otherwise returns 0.
 */


// Function to check if an IP address is assigned to any interface
int ip_assigned(const char *ip_address) 
{
    // Execute the command "ip addr show"
    FILE *fp = popen("ip addr show", "r");
    if (fp == NULL) 
    {
        perror("Error executing ip command");
        exit(EXIT_FAILURE);
    }

    char line[LINE_SIZE];
    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        // Check if the line contains the IP address
        if (strstr(line, ip_address) != NULL) 
	{
            pclose(fp);
            return VALID_IP; // IP address is assigned to an interface
        }
    }

    pclose(fp);
    return INVALID_IP; // IP address is not assigned to any interface
}

/*Function name:
 * 	ping_ip - Execute a ping command to the specified IP address.
 *
 * 	parameters - ip_address
 *
 * 	Return value:
 * 		None
 */

void ping_ip(const char *ip_address) 
{
    // Execute the ping command
    char command[COMMAND_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", ip_address);
    DIR_LOG("Executing command: %s\n", command);
    int status = system(command);

    if (status == ERROR_STATUS) 
    {
        perror("Error executing ping command");
	return ERROR_STATUS; 
    } 
    else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
    {
        DIR_LOG(stderr, "Ping command exited with non-zero status\n");
	return ERROR_STATUS; 
    }
    else
	    printf("Ping Successfully\n");
}

/* Function name
 * 	ethernet_main - This function perform loopback test for ethernet interface.
 *
 * parameters
 * 	The number of command-line arguments.
 * 	The array of command-line arguments.
 *
 * Return value
 * 	i. If the value is 0, the function returns successful.
 * 	ii. If the value is not zero, then the function return with the error code.
 */
int ethernet_main(char *argv) 
{
    DIR_LOG("IP Address: %s\n", argv);
    // Check the length of the input IP address
    if (strlen(argv) > MAX_IP_LENGTH) 
    {
        DIR_LOG(stderr, "Error: Invalid IP address length\n");
	return ERROR_STATUS; 
    }

#if 0
    // Check if the provided IP address is assigned to any interface
    if (!ip_assigned(argv)) 
    {
        DIR_LOG("IP address %s is not assigned to any interface.\n", argv);
        exit(EXIT_FAILURE);
    }

    // Ping the provided IP address
    DIR_LOG("IP address %s is assigned to an interface.\n", argv);
#endif
    ping_ip(argv);

    return DIR_SUCCESS;
}

