/*
 * Protocol.c
 *
 *  Created on: Dec 29, 2013
 *      Author: User
 */

#include "Default.h"

#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif

#if SPI

void SPI_SendData(int SendData)
{
	int TempBuffer;
	LPC_SSP1->ICR = 3;									// Clear Interrupts

	while ( LPC_SSP1->SR & ( 1 << 2 ) )					//Check if Receive Buffer is empty
	{
		TempBuffer = LPC_SSP1->DR;
	}

	while ( ( LPC_SSP1->SR & ( 1 << 0 ) ) == 0 );		// Check if Transmit Buffer is empty
	LPC_SSP1->DR = SendData;							// Send Data

	while ( ( LPC_SSP1->SR & ( 1 << 2 ) ) == 0 );		// Check if Receive Buffer is empty
	LPC_SSP1->DR;										// Read Data
}

int SPI_ReceiveData(void)
{
	int TempBuffer;
	LPC_SSP1->ICR = 3;									// Clear Interrupts

	while ( LPC_SSP1->SR & ( 1 << 2 ) )					//Check if Receive Buffer is empty
	{
		TempBuffer = LPC_SSP1->DR;
	}
	while ( ( LPC_SSP1->SR & ( 1 << 0 ) ) == 0 );		// Check if Transmit Buffer is empty
	LPC_SSP1->DR = 0x00;								// Send Data

	while ( ( LPC_SSP1->SR & ( 1 << 2 ) ) == 0 );		// Check if Receive Buffer is empty
	return ( LPC_SSP1->DR);								// Read Data
}

#endif


