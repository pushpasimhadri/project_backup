/****************************************************************************
 * FileName:    ddr.h
 * Author:      Ragul M
 * Date:        May 07 2024
 * Description:
 *              Header file for DDR interface.
 * Version:     1.0
 **************************************************************************/


/* Header FIles */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

/* Macros */
#define DIR_SUCCESS         0x00               /* Success code */
#define DIR_ERRLOG 	    printf             /* Macro for error messages */
#define DIR_LOG 	    printf             /* Macro for info messages */
#define DDR_TEST_SIZE	    (2 * 1024 * 1024)  // Size of DDR test in bytes
#define DIR_FAILURE	    -1                 /* Failure code */
#define DIR_INITVALUE	    0		       /* Initialization value */
#define DDR_MINSIZE	    1		       /* DDR minium size */
#define DDR_MAXSIZE	    (10 * 1024 * 1024) /* DDR maximum size */

/*Function name:
 *      ddr_main - This function read and write the values in DDR memory.
 *
 * Parameters:
 *      None
 *
 * ReturnValue:
 *      i. If the value is 0, the function returns successful.
 *      ii. If the value is not zero, then the function return with the error code.
 */
int ddr_main(void);
short writein_ddrmem(uint8_t *in_pDdrAddr, size_t in_uiSize);
short readin_ddrmem(uint8_t *in_pDdrAddr, size_t in_uiSize);

