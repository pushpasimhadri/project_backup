/****************************************************************************
 * FileName:    ddr.c
 * Author:      Ragul M
 * Date:        May 07 2024
 * Description:
 *              To verify PS DDR memory by write and read.
 * Version:     1.0
 **************************************************************************/

#include "ddr.h"

/*Function name:
 * 	ddr_main - This function allocate memory in DDR dynamically.
 *
 * Parameters:
 * 	None
 *
 * ReturnValue:
 * 	i. If the value is 0, the function returns successful.
 * 	ii. If the value is not zero, then the function return with the error code.
 */
int ddr_main(void) 
{
	uint8_t *pDdrMem = NULL;
	int16_t sRetVal = DIR_SUCCESS;
	
	/* Allocate 1MB memory for DDR Test */
	pDdrMem = malloc(DDR_TEST_SIZE);
	if(pDdrMem == NULL)
	{
		DIR_ERRLOG("ERROR:\t Memory allocation failed\n");
		return DIR_FAILURE;
	}

	/* Function call to write in DDR memory */
	sRetVal = writein_ddrmem(pDdrMem, DDR_TEST_SIZE);
	if(sRetVal != DIR_SUCCESS)
	{
		DIR_ERRLOG("ERROR\t: Write in DDR Memory failed %hd\n", sRetVal);
		free(pDdrMem);
		return DIR_FAILURE;
	}

	/* Function call to read and validate DDR memory */
	sRetVal = readin_ddrmem(pDdrMem, DDR_TEST_SIZE);
	if(sRetVal != DIR_SUCCESS)
	{
		DIR_ERRLOG("ERROR\t: Read in DDR Memory failed %hd\n", sRetVal);
		free(pDdrMem);
		return DIR_FAILURE;
	}
	
	free(pDdrMem);
	return DIR_SUCCESS;
}

/*Function name:
 * 	writein_ddrmem - This function used to write counter data in DDR memory.
 *
 * Parameters:
 * 	in_pDdrAddr, in_uiSize	
 *
 * ReturnValue:
 * 	i. If the value is 0, the function returns successful.
 * 	ii. If the value is not zero, then the function return with the error code.
 */
short writein_ddrmem(uint8_t *in_pDdrAddr, size_t in_uiSize)
{
	size_t uiLoop = DIR_INITVALUE;

	/* Validate input args */
	if(in_pDdrAddr == NULL)
	{
		DIR_ERRLOG("ERROR\t: Invalid input pointer for writein_ddrmem\n");
		return DIR_FAILURE;
	}
	if( (in_uiSize < DDR_MINSIZE) || (in_uiSize > DDR_MAXSIZE) )
	{
		DIR_ERRLOG("ERROR\t: Invalid input size for writein_ddrmem %u\n", in_uiSize);
		return DIR_FAILURE;
	}

	/* Write counter data in DDR memory */
	for(uiLoop = DIR_INITVALUE; uiLoop < in_uiSize; uiLoop++)
	{
		in_pDdrAddr[uiLoop] = (uint8_t)(uiLoop % 256);
	}

	return DIR_SUCCESS;
}

/*Function name:
 * 	readin_ddrmem - This function used to read data in DDR memory and verify.
 *
 * Parameters:
 * 	in_pDdrAddr, in_uiSize	
 *
 * ReturnValue:
 * 	i. If the value is 0, the function returns successful.
 * 	ii. If the value is not zero, then the function return with the error code.
 */
short readin_ddrmem(uint8_t *in_pDdrAddr, size_t in_uiSize)
{
	size_t uiLoop = DIR_INITVALUE;

	/* Validate input args */
	if(in_pDdrAddr == NULL)
	{
		DIR_ERRLOG("ERROR\t: Invalid input pointer for readin_ddrmem\n");
		return DIR_FAILURE;
	}
	if( (in_uiSize < DDR_MINSIZE) || (in_uiSize > DDR_MAXSIZE) )
	{
		DIR_ERRLOG("ERROR\t: Invalid input size for readin_ddrmem %u\n", in_uiSize);
		return DIR_FAILURE;
	}	

	/* Read data in DDR memort */
	for(uiLoop = DIR_INITVALUE; uiLoop < in_uiSize; uiLoop++)
	{
		/* Validating the data */
		if( in_pDdrAddr[uiLoop] != (uint8_t)(uiLoop % 256) )
		{
			break;
		}
	}
	if(uiLoop < in_uiSize)
	{
		return DIR_FAILURE;
	}

	return DIR_SUCCESS;
}
