/*
 *************************************************************************************
 *
 *   Filename:       main.c
 *   Date:           January 5,2007
 *   File Version:   1.00
 *
 *   Company:        Emertxe Information Technologies Pvt Ltd.
 *
 *************************************************************************************
 *
 *    Files required:
 *          main.h
 *
 *************************************************************************************
 */
#include"main.h"
#include"switch.h"

__CONFIG(DEBUG_OFF & LVP_OFF & FCMEN_OFF & IESO_OFF & BOREN_OFF & CPD_OFF & CP_OFF & MCLRE_ON & PWRTE_ON & WDTE_OFF & FOSC_HS);
__CONFIG(WRT_OFF & BOR4V_BOR40V);

/*static void glow_leds(unsigned char switch_pressed)
{
	if (switch_pressed == SWITCH1)
	{
		RD0 = !RD0;
	}
	if (switch_pressed == SWITCH2)
	{
		RD1 = !RD1;
	}
	if (switch_pressed == SWITCH3)
	{
		RD2 = !RD2;
	}
	if (switch_pressed == SWITCH4)
	{
		RD3 = !RD3;
	}
	if (switch_pressed == SWITCH5)
	{
		RD4 = !RD4;
	}
	if (switch_pressed == SWITCH6)
	{
		RD5 = !RD5;
	}
}*/

int pswd_chk(unsigned char switch_pressed)
{
    int count = 0;

   if( (switch_pressed == 0x01 && count == 0) || (switch_pressed == 0x02 && count == 1) || (switch_pressed == 0x04 && count == 2)
    || (switch_pressed == 0x08 && count == 3) || (switch_pressed == 0x10 && count == 4) || (switch_pressed == 0x20 && count == 5) )

    count++;


    if( count == 5)
    return(1);
    else return(0);
}


static void init_config(void)
{
	/* Setting PORTB as Digital Port */
	ANSELH = 0x00;

	/* Setting PORTD as Output Port */
	TRISD = 0x00;

	DISABLE_LED;
}

void main(void)
{
	init_config();
	int flag=0;

	while (flag == 0)
	{
		flag = pswd_chk(read_switches(1));
    }

    RD0 = !RD0;
}