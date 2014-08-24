#include"main.h"
#include"switch.h"
#include <pic.h>

__CONFIG(DEBUG_OFF & LVP_OFF & FCMEN_OFF & IESO_OFF & BOREN_OFF & CPD_OFF & CP_OFF & MCLRE_ON & PWRTE_ON & WDTE_OFF & FOSC_HS);
__CONFIG(WRT_OFF & BOR4V_BOR40V);

static void glow_leds(unsigned char switch_pressed)
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
}

static void init_config(void)
{
	/* Setting PORTB as Digital Port */
	ANSELH = 0x00;

	/* Setting PORTD as Output Port */
	TRISD = 0x00;

	DISABLE_LED;
}


unsigned char read_switches(unsigned char detection_type)
{
	static unsigned char pres_state_of_switches = DEFAULT_INPUT_LEVEL; //0x3F
	static unsigned char prev_state_of_switches = DEFAULT_INPUT_LEVEL;  //0x3F
	unsigned char bounce_delay;

	/* If you have multiplexed inputs using PIC controllers */
	SET_INPUTS;
	if (DETECT_STATE)
	{
		/* Capturing the states of inputs */
		prev_state_of_switches = pres_state_of_switches;
	}

	/* Read the i/p from the switches */
	pres_state_of_switches = PORT & DEFAULT_INPUT_LEVEL;
	/* If you have multiplexed inputs using PIC controllers */
	RESET_INPUTS;
	
	for (bounce_delay = 1000; bounce_delay--;); /* TODO: Correct code to check Bounsing */

	if ((pres_state_of_switches != DEFAULT_INPUT_LEVEL) && DETECT_STATE)
	{
		return (pres_state_of_switches ^ prev_state_of_switches);
	}
	else
	{
		return pres_state_of_switches;
	}
}

void main(void)
{
	init_config();

	while (1)
	{
		glow_leds(read_switches(1));
	}
}
