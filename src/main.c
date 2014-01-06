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

//#ifndef ININT_H_
	#include "Initializations.h"
//#endif
//#include "Initializations.h"
//#include <stdio.h>

int gTemp = 0;  //Global variable

int g_for_0 = 0;	// Temporary Global variable used for for-loop
int g_for_1 = 0;	// Temporary Global variable used for for-loop
int g_for_2 = 0;	// Temporary Global variable used for for-loop


// TODO: insert other definitions and declarations here

int main(void)
{

	HardwareInitializations();		//All hardware peripherals are initialised here

	Testing_noWhileLoop();


	while(1)
	{
		Testing_inWhileLoop();

	} // while (1)
	return 0 ;
} // main()
