#include "Default.h"
#include "initializations.h"

#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif

#if UART
void UART_printf(char dummy[])
{
	int n=0;
	while( dummy[n] != '\0' )
	{
		while( ( LPC_UART3->LSR & 1 << 5 ) == 0 );
		LPC_UART3->THR = dummy [n];
		n++;
	}
}



#endif // #if UART
