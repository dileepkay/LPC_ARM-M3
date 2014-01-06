#include "Default.h"

#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif

//void Initializations()
//{


#if SYSTICK_TIMER
// -----------------------------------------
// Definition :: System Timer Initialization 
// -----------------------------------------
void SYSTICK_init(void)
{
	//Set value for Systick Reload Value Register.
	SysTick->LOAD = 999999;
	//Clear Systick Current Value Register.
	SysTick->VAL = 0;
	//Enable Systick Counter, Systick Interrupt and Select CPU clock as clock source.
	SysTick->CTRL = 7;
}
#endif


#if RGBLED
// -----------------------------------------
// RGB LED Initialization 
// -----------------------------------------
void RGBLED_init()
{
	LPC_PINCON->PINSEL4 &= (~ ( 3 << 0 ) ); 	// Select P2.0 which is connected to Red LED of RGB
	LPC_GPIO2->FIODIR |= ( 1 << 0 );			// Setting of Direction as Output

	LPC_PINCON->PINSEL4 &= (~ ( 3 << 2 ) ); 	// Select P2.1 which is connected to Green LED of RGB
	LPC_GPIO2->FIODIR |= ( 1 << 1 );			// Setting of Direction as Output

	LPC_PINCON->PINSEL1 &= (~ ( 3 << 20 ) ); 	// Select P0.26 which is connected to Blue LED of RGB
	LPC_GPIO0->FIODIR |= ( 1 << 26 );			// Setting of Direction as Output
}
#endif

#if JOYSTICK
void JoyStick_init()
{
	LPC_PINCON->PINSEL0 &= (~ ( 3 << 30 ) );
	LPC_GPIO0->FIODIR &= ( ~ ( 1 << 15 ) );       	// 0.15 Left
	LPC_PINCON->PINMODE0 &= (~ ( 3 << 30 ) );

	LPC_PINCON->PINSEL1 &= (~ ( 3 << 0 ) );
	LPC_GPIO0->FIODIR &= ( ~ ( 1 << 16 ) );			// 0.16 Up
	LPC_PINCON->PINMODE0 &= (~ ( 3 << 0 ) );

	LPC_PINCON->PINSEL4 &= (~ ( 3 << 6 ) );
	LPC_GPIO2->FIODIR &= ( ~ ( 1 << 3 ) ); 			// 2.3 Right
	LPC_PINCON->PINMODE4 &= (~ ( 3 << 6 ) );

	LPC_PINCON->PINSEL1 &= (~ ( 3 << 2 ) );
	LPC_GPIO0->FIODIR &= ( ~ ( 1 << 17 ) );			// 0.17 Centre
	LPC_PINCON->PINMODE1 &= (~ ( 3 << 2 ) );

	LPC_PINCON->PINSEL4 &= (~ ( 3 << 8 ) );
	LPC_GPIO2->FIODIR &= ( ~ ( 1 << 4 ) );			// 2.4 Down
	LPC_PINCON->PINMODE4 &= (~ ( 3 << 8 ) );

}
#endif

#if UART
void UART_IO_init(void)
{
	LPC_PINCON->PINSEL0 |= ( 2 << 0 );			// Set P0.0 to Binary 10 - TXD3
	LPC_PINCON->PINSEL0 |= ( 2 << 2 );			// Set P0.1 to Binary 10 - RXD3

	LPC_PINCON->PINMODE0 |= ( 2 << 0 );			// Set P0.0 and P0.1 to Binary 10 - Pin has neither pull-up nor pull-down resistor enabled
	LPC_PINCON->PINMODE0 |= ( 3 << 2 );
}

void UART_init(void)
{
	LPC_SC->PCONP |= (1 << 25);					//Turn on Power for UART Interface

	LPC_SC->PCLKSEL1 &= (~(3 << 18)) ;			//Set PCLK_UART3 to CCLK/4 - 25MHz

	LPC_UART3->LCR |= (3 << 0);					//Set Data Format: 8 bit Data, 1 Stop Bit,
	LPC_UART3->LCR &= (~(1 << 2));

	LPC_UART3->LCR |= (1 << 7);					// Set BaudRate to 115200bps
	LPC_UART3->DLM = 0;
	LPC_UART3->DLL = 9;
	LPC_UART3->FDR = 0x21;
	LPC_UART3->LCR &= (~(1 << 7));

	LPC_UART3->FCR |= (1 << 0);					//Enable FIFO

	LPC_UART3->IER |= (3 << 0);					//Enable Interrupts

	LPC_UART3->TER |= (1 << 7);					// Enable Transmission
}
#endif //#if UART

#if LED2
void LED2_init()
{
	LPC_PINCON->PINSEL1 &= (~ ( 3 << 12 ) ); 	// Select P0.22 which is connected to LED2 of the board
	LPC_GPIO0->FIODIR |= ( 1 << 22 );			// Setting of Direction as Output
}
#endif

#if PBUTTON_4
void PButton4_init()
{
	LPC_PINCON->PINSEL3 &= (~ ( 3 << 30 ) );	// Select P1.31 which is connected to SW4 Push Button of the board
	LPC_GPIO1->FIODIR &= ( ~ ( 1 << 31 ) ); 	// Set P1.31 to 0 - to set direction as Input
	LPC_PINCON->PINMODE3 &= (~ ( 3 << 30 ) );	// Set P1.31 to 00 - to enable on-chip pull up resistor
}
#endif

#if PBUTTON_3
void PButton3_init()
{
#if INTERRUPT
	LPC_PINCON->PINSEL4 |= ( 1 << 20 );			// Select P2.10 which is connected to SW3 Push Button of the board
	LPC_PINCON->PINMODE4 &= (~ ( 3 << 20 ) );	// Set P2.10 to 00 - to enable on-chip pull up resistor

	NVIC_SetPriorityGrouping(4);				// Set Priority Groupt to 3:2
	NVIC_SetPriority(EINT0_IRQn, 0 );			// Set Priority Level to 1
	NVIC_EnableIRQ(EINT0_IRQn);					// Set Enable Interrupt to 1
#else
	LPC_PINCON->PINSEL4 &= ( ~ ( 3 << 20 ) );	// Select P2.10 which is connected to SW3 Push Button of the board
	LPC_GPIO2->FIODIR &= ( ~ ( 1 << 21 ) ); 	// Set P2.10 to 0 - to set direction as Input
	LPC_PINCON->PINMODE4 &= (~ ( 3 << 20 ) );	// Set P2.10 to 00 - to enable on-chip pull up resistor
#endif
}
#endif

#if SPI
void SPI_init()
{
	LPC_SC->PCONP |= ( 1<< 10); 				// Turn on power for SSPI module
	LPC_SC->PCLKSEL0 &= ( ~ ( 3 << 20 ) );		// SPI Clock Rate to 6.25 MHz
	LPC_SSP1->CPSR = 2;
	LPC_SSP1->CR0 |= ( 1 << 8 );
	LPC_SSP1->CR0 |= ( 7 << 0 );				// Configure SSP1: DataSize = 8, FrameFormat = SPI, CPOL = 0, CPHA = 0
	LPC_SSP1->CR1 |= ( 0 << 2 );				// Set Master Mode & enable SSP1
	LPC_SSP1->CR1 |= ( 1 << 1 );
}

void SPI_IO_init()
{
	LPC_PINCON->PINSEL0  |= ( 2 << 14 );			//Set P0.7, P0.8, P0.9 to Binary 10 - SCK1, MISO1, MOSI1
	LPC_PINCON->PINSEL0  |= ( 2 << 16 );
	LPC_PINCON->PINSEL0  |= ( 2 << 18 );

	LPC_PINCON->PINMODE0 &= ( ~ ( 3 << 14 ) );	// Set P0.7, P0.8, P0.9 to Binary 00 - OnChip pull-up resistor enabled
	LPC_PINCON->PINMODE0 &= ( ~ ( 3 << 16 ) );
	LPC_PINCON->PINMODE0 &= ( ~ ( 3 << 18 ) );

	LPC_PINCON->PINSEL4  &= ( ~ ( 3 << 4 ) );	// Set P2.2 to GPIO, Output, Enable Pull-up
	LPC_PINCON->PINMODE4 &= ( ~ ( 3 << 4 ) );
	LPC_GPIO2->FIODIR |= ( 1 << 2 );
	LPC_GPIO2->FIOSET |= ( 1 << 2 );			// Set to High Output
}
#endif

#if SEVEN_SEGMENT
void Seven_Segment_init()
{


// -------------------------------------------------
// Byte formation for Data for SevenSegment
//
// 	F | C | Dp | B | A | G | E | D
//	1 | 1 | 1  | 0 | 0 | 0 | 0 | 0 		// Active Low
//
//			  A
//			  __
//		   F| 	 |B
//			 G__
//		   E|	 |C
//			  __  .Dp
//			   D
// -------------------------------------------------


}
#endif

#if I2C
void I2C_IO_init()
{
	LPC_PINCON->PINSEL0 |= ( 2 << 20 );				// Set P0.10 and P0.11 to Binary 10 - SDA2 and SCL2
	LPC_PINCON->PINSEL0 |= ( 2 << 22 );

	LPC_PINCON->PINMODE0 &= ( ~ ( 3 << 20 ) );		// Set P0.10 and P0.11 to Binary 10 - enable on-chip pull-up resistor
	LPC_PINCON->PINMODE0 &= ( ~ ( 3 << 22 ) );
}

void I2C_init(void)
{
	LPC_SC->PCONP	 |= ( 1 << 26 );									// Turn on power for I2C2 module

	LPC_SC->PCLKSEL1 |= ( 2 << 20 );									// Set I2C2 Clock Rate to 100KHz ( CCLK/2 = 50MHz)
	LPC_I2C2->I2SCLH = 250;
	LPC_I2C2->I2SCLL = 250;

	LPC_I2C2->I2CONCLR = ( ( 1 << 2 ) | ( 1 << 5 ) | ( 1 << 6 ) ); 		//Set I2C operation to default, I2C control Clear Register

	LPC_I2C2->I2CONSET = ( 1 << 6 );									// Enable I2C Interface
}
#endif

//}
