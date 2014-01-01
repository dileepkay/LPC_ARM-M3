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
#endif //#if SPI

#if I2C

int I2C_Start (void)
{
	LPC_I2C2->I2CONCLR	= ( 1 << 3 );						// Clear Interrupt
	LPC_I2C2->I2CONSET	= ( 1 << 5 );						// Set Start Flag

	while ( ( LPC_I2C2->I2CONSET & ( 1 << 3 ) ) == 0 );		// Wait for Interrupt

	LPC_I2C2->I2CONCLR = ( 1 << 5 );						// Clear Flag

	return ( LPC_I2C2->I2STAT & 0xF8 );						// Return status

}

void I2C_Stop (void)
{
	LPC_I2C2->I2CONCLR = ( 1 << 3 );						// Clear Interrupt
	LPC_I2C2->I2CONSET = ( 1 << 4 );						// Set Stop Flag
}

int I2C_SendByte(int DataByte)
{
	LPC_I2C2->I2CONCLR = ( 1 << 3 );						// Clear Interrupt
	LPC_I2C2->I2DAT = DataByte & 0xFF;						// Send DataByte

	while ( ( LPC_I2C2->I2CONSET & ( 1 << 3 ) ) == 0 );		// Wait for Interrupt

	return ( LPC_I2C2->I2STAT & 0xF8 );
}

int I2C_GetByte(int ack)
{
	if ( ack == 1 )
	{
		LPC_I2C2->I2CONSET = ( 1 << 2 );						// Set Acknowledgement Flag
	}
	else
	{
		LPC_I2C2->I2CONCLR = ( 1 << 2 );						// Clear Acknowledgement Flag
	}

	LPC_I2C2->I2CONCLR = ( 1 << 3 );						// Clear Interrupt

	while ( ( LPC_I2C2->I2CONSET & ( 1 << 3 ) ) == 0 );		// Wait for Interrupt

	if ( ( ( LPC_I2C2->I2STAT & 0xF8 ) == 0x50 ) | ( ( LPC_I2C2->I2STAT & 0xF8 ) == 0x58 ) )
	{
		return (LPC_I2C2->I2DAT & 0xFF );
	}
	return 0;
}
#endif // #if I2C


