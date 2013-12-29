#include "Default.h"

#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif

extern int gTemp;

#if SYSTICK_TIMER
// -----------------------------------------
// System Timer Handler  
// -----------------------------------------
void SysTick_Handler(void)
{
	printf("Systic Counting %d\n",gTemp);
	gTemp++;
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




