/*
===============================================================================
 Name        : main.c
 Author      : Dileepkay
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "Default.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP;


#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif
#ifdef ININT_H_
	#include "Initializations.h"
#endif
//#include "Initializations.h"
#include <stdio.h>
int gTemp = 0;  //Global variable


// TODO: insert other definitions and declarations here

int main(void)
{

	HardwareInitializations();		//All hardware peripherals are initialised here

/*
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
	#endif //#if LED

	#if PBUTTON_4
		PButton_init();
	#endif

//*/

	while(1)
	{
		Testing ();					// All features testing is defined here

/*
	#if RGB_TESTING
		LPC_GPIO0->FIOCLR = ( 1 << 26 );	// Blue
		LPC_GPIO2->FIOCLR = ( 1 << 0 );		// Red
		LPC_GPIO2->FIOCLR = ( 1 << 1 );		// Green

		for ( temp = 0; temp < 10000000; temp++ );
		LPC_GPIO2->FIOSET = (1 << 0);

		for ( temp = 0; temp < 10000000; temp++ );
		LPC_GPIO2->FIOSET = (1 << 1);
		LPC_GPIO2->FIOCLR = (1 << 0);

		for ( temp = 0; temp < 10000000; temp++ );
		LPC_GPIO0->FIOSET = (1 << 26);
		LPC_GPIO2->FIOCLR = (1 << 1);

		for ( temp = 0; temp < 10000000; temp++ );
	#endif //#if RGB_TESTING

	#if LED_TESTING
		LPC_GPIO0->FIOSET = ( 1 << 22 );
		for ( temp = 0; temp < 1000000; temp++ );
		LPC_GPIO0->FIOCLR = ( 1 << 22 );
		for ( temp = 0; temp < 1000000; temp++ );
	#endif

	#if PUSHBUTTON_TESTING
		temp = LPC_GPIO1->FIOPIN & ( 1 << 31 ); // Read data from P1.31
		printf( "\nData from SW4 = %d", temp );

	#endif

	#if LED_PBUTTON_TESTING
		if  ( ( LPC_GPIO1->FIOPIN & ( 1 << 31 ) ) == 0 )
		{
			LPC_GPIO0->FIOSET = ( 1 << 22 );
		}
		else
		{
			LPC_GPIO0->FIOCLR = ( 1 << 22 );
		}
	#endif

	#if JOYSTICK_TESTING
		if ( ( ( LPC_GPIO0->FIOPIN & ( 1 << 15 ) ) == 0 ) ||
			 ( ( LPC_GPIO0->FIOPIN & ( 1 << 16 ) ) == 0 ) ||
			 ( ( LPC_GPIO2->FIOPIN & ( 1 << 03 ) ) == 0 ) ||
			 ( ( LPC_GPIO2->FIOPIN & ( 1 << 04 ) ) == 0 ) )

		{
			LPC_GPIO0->FIOSET = ( 1 << 22 );
		}
		else
		{
			LPC_GPIO0->FIOCLR = ( 1 << 22 );
		}
	#endif

	#if	RGB_JOYSTICK_TESTING
		if ( ( ( LPC_GPIO0->FIOPIN & ( 1 << 15 ) ) == 0 ) ) // Left
		{
			LPC_GPIO0->FIOSET = (1 << 26);		// Blue
			LPC_GPIO2->FIOCLR = (1 << 0);		// Red
			LPC_GPIO2->FIOCLR = (1 << 1);		// Green
		}
		else if ( ( ( LPC_GPIO0->FIOPIN & ( 1 << 16 ) ) == 0 ) ) // Up
		{
			LPC_GPIO0->FIOCLR = (1 << 26);		// Blue
			LPC_GPIO2->FIOSET = (1 << 0);		// Red
			LPC_GPIO2->FIOCLR = (1 << 1);		// Green
		}
		else if ( ( ( LPC_GPIO2->FIOPIN & ( 1 << 3 ) ) == 0 ) ) // Right
		{
			LPC_GPIO0->FIOCLR = (1 << 26);		// Blue
			LPC_GPIO2->FIOCLR = (1 << 0);		// Red
			LPC_GPIO2->FIOSET = (1 << 1);		// Green
		}
		else if ( ( ( LPC_GPIO0->FIOPIN & ( 1 << 17 ) ) == 0 ) ) // Center
		{
			LPC_GPIO0->FIOSET = (1 << 26);		// Blue
			LPC_GPIO2->FIOSET = (1 << 0);		// Red
			LPC_GPIO2->FIOSET = (1 << 1);		// Green
		}
		else if ( ( ( LPC_GPIO2->FIOPIN & ( 1 << 4 ) ) == 0 ) ) // Down
		{
			LPC_GPIO0->FIOCLR = (1 << 26);		// Blue
			LPC_GPIO2->FIOCLR = (1 << 0);		// Red
			LPC_GPIO2->FIOCLR = (1 << 1);		// Green
		}
	#endif
// */

	} // while (1)
	return 0 ;
} // main()
