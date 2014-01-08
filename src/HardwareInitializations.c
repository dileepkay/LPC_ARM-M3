/*
 * HardwareInitializations.c
 *
 *  Created on: Dec 28, 2013
 *      Author: User
 */
#include "Default.h"
#include "Initializations.h"


void HardwareInitializations()
{
	#if UART
		UART_IO_init();
		UART_init();

		UART_printf("\n\r===============");
		UART_printf("\n\rProgram Started");
		UART_printf("\n\r===============");

	#endif //#if UART

	#if RGBLED
		RGBLED_init();
	#endif //#if RGBLED

	#if SYSTICK_TIMER
		SYSTICK_init();
	#endif //#if SYSTICK_TIMER

	#if LED2
		LED2_init();
	#endif //#if LED2

	#if PBUTTON_4
		PButton4_init();
	#endif

	#if PBUTTON_3
		PButton3_init();
	#endif

	#if SPI
		SPI_IO_init();
		SPI_init();
	#endif

	#if SEVEN_SEGMENT
		Seven_Segment_init();
	#endif

	#if I2C
		I2C_IO_init();
		I2C_init();
	#endif

}
