#include "Default.h"

#if UART

char a;

PIN_init();
UART_init();
while ((LPC_UART3->LSR & 1 << 5) == 0);
LPC_UART3->THR = 'A';
while ((LPC_UART3->LSR & 1 << 0) == 0);
a = LPC_UART3->RBR;
if (a == 'b' || a == 'B')
{
	while ((LPC_UART3->LSR & 1 << 5) == 0);
	LPC_UART3->THR = 'O';
	while ((LPC_UART3->LSR & 1 << 5) == 0);
	LPC_UART3->THR = 'K';
}
#endif // #if UART
