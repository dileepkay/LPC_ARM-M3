#include "Default.h"

#ifndef ININT_H_
	#include "Initializations.h"
#endif


#ifdef __USE_CMSIS
	#include "LPC17xx.h"
#endif
extern int gTemp;
//extern int g_for_0;
//extern int g_for_1;

void Testing ( void )

{
	#if RGB_TESTING
		LPC_GPIO0->FIOCLR = ( 1 << 26 );	// Blue
		LPC_GPIO2->FIOCLR = ( 1 << 0 );		// Red
		LPC_GPIO2->FIOCLR = ( 1 << 1 );		// Green

		for ( gTemp = 0; gTemp < 10000000; gTemp++ );
		LPC_GPIO2->FIOSET = (1 << 0);

		for ( gTemp = 0; gTemp < 10000000; gTemp++ );
		LPC_GPIO2->FIOSET = (1 << 1);
		LPC_GPIO2->FIOCLR = (1 << 0);

		for ( gTemp = 0; gTemp < 10000000; gTemp++ );
		LPC_GPIO0->FIOSET = (1 << 26);
		LPC_GPIO2->FIOCLR = (1 << 1);

		for ( gTemp = 0; gTemp < 10000000; gTemp++ );
	#endif //#if RGB_TESTING

	#if LED2_TESTING
		LPC_GPIO0->FIOSET = ( 1 << 22 );
		for ( gTemp = 0; gTemp < 1000000; gTemp++ );
		LPC_GPIO0->FIOCLR = ( 1 << 22 );
		for ( gTemp = 0; gTemp < 1000000; gTemp++ );
	#endif

	#if PUSHBUTTON_TESTING
		#if PBUTTON_4
			gTemp = LPC_GPIO1->FIOPIN & ( 1 << 31 ); // Read data from P1.31
			printf( "\nData from SW4 = %d", gTemp );
		#endif

		#if PBUTTON_3
			gTemp = LPC_GPIO2->FIOPIN & ( 1 << 20 ); // Read data from P2.10
			printf( "\nData from SW3 = %d", gTemp );
		#endif
	#endif

	#if LED2_PBUTTON_TESTING
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

	#if SEVEN_SEGMENT_TESTING

		//extern char Codes[10];
		for ( g_for_1 = 0; g_for_1 < 10; g_for_1++)
		{
			M_Enable_CS;
			SPI_SendData( Codes[g_for_1] );
			M_Disable_CS;
			for (g_for_0=0; g_for_0<10000000; g_for_0++);
		}
	#endif

	#if I2C

	int i = 0, j = 0;
	int datawrite[5] = { 0xF0, 0x01, 0x03, 0x05, 0x07 };
	int dataread[4];

	while(1)
	{
		if ( I2C_Start() == 0x08 )
		{
			if ( I2C_SendByte(0xA0) == 0x18 )
			{
				for (i=0; i<5; i++)
				{
					I2C_SendByte(datawrite[i]);
				}
			}
		}
		I2C_Stop();

		for (j=0; j<100000; j++);

		for (i=1; i<5; i++)
		{
			printf("Data written is %x \n", datawrite[i]);
		}

		if ( I2C_Start() == 0x08 )
		{
			if ( I2C_SendByte(0xA0) == 0x18 )
			{
				if (I2C_SendByte(0xF0) == 0x28 )
				{
					if( I2C_Start() == 0x10 )
					{
						if( I2C_SendByte(0xA1) == 0x40 )
						{
							for ( i=0; i<3; i++ )
							{
								dataread[i] = I2C_GetByte(1);
							}
								dataread[3] = I2C_GetByte(0);
						}
					}
				}
			}
		}
		I2C_Stop();

		for (i=0; i<4; i++)
		{
			printf("Data Read is %x\n", dataread[i]);
		}
	}

	#endif

}

