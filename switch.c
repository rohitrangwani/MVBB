#include <pic.h>
#include "switch.h"

unsigned char read_switches(unsigned char detection_type)
{
	static unsigned char pres_state_of_switches = DEFAULT_INPUT_LEVEL;
	static unsigned char prev_state_of_switches = DEFAULT_INPUT_LEVEL;
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
	
	for (bounce_delay = 250; bounce_delay--;); /* TODO: Correct code to check Bounsing */

	if ((pres_state_of_switches != DEFAULT_INPUT_LEVEL) && DETECT_STATE)
	{
		return (pres_state_of_switches ^ prev_state_of_switches);
	}
	else
	{
		return pres_state_of_switches;
	}
}
