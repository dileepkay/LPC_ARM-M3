#include "Default.h"
#include "Initializations.h"

#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif

//extern int gTemp;

#if SYSTICK_TIMER
// -----------------------------------------
// System Timer Handler  
// -----------------------------------------
void SysTick_Handler(void)
{
	gTemp ^= TRUE;
//	( ( gTemp ) ? LPC_GPIO0->FIOSET = ( 1 << 22 ) : LPC_GPIO0->FIOCLR = ( 1 << 22 ) );      // Not Working
	if ( gTemp )
	{
		LPC_GPIO0->FIOSET = ( 1 << 22 );
	}
	else
	{
		LPC_GPIO0->FIOCLR = ( 1 << 22 );
	}

#if DEBUG_PRINT
	UART_printf("\n\rSystic Counting = ");
	UART_printf(itoa(gTemp));
#endif

}
#endif 

#if INTERRUPT
void EINT0_IRQHandler(void)
{
	int run1 = 20;
	int LED_Status = 0;
	int i;
	while( run1 != 0 )
	{
		if ( LED_Status == 0 )
		{
			LPC_GPIO0->FIOSET = ( 1 << 22 );
			for ( i = 0; i < 1000000; i++ );
			LED_Status = 1;
		}
		else
		{
			LPC_GPIO0->FIOCLR = ( 1 << 22 );
			for ( i = 0; i < 1000000; i++ );
			LED_Status = 0;
		}
	}
}
#endif // INTERRUPT




