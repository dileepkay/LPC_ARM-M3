/*
 * HardwareInitializations.c
 *
 *  Created on: Dec 28, 2013
 *      Author: User
 */
#include "Default.h"

void HardwareInitializations(void)
{
	#if RGBLED
		RGBLED_init();
	#endif //#if RGBLED

	#if SYSTICK_TIMER
		SYSTICK_init();
	#endif //#if SYSTICK_TIMER

	#if UART
		UART_init();
	#endif //#if UART

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

}