#include "main.h"
#include "timers.h"
#include "clcd.h"

void interrupt isr(void)
{
	if (T0IF)
	{
		/*
		 * XTAL = 20MHz
		 * We will set prescaler value of 2 to achieve 400ns with 200ns
		 * instruction cycle, i.e. increment counter every 400ns and hence
		 * generate interrupt after 102.8us, but we need 100us, so
		 * starting from 8, i.e. a value of 6, and
		 * + 1 for extra cycles, caused by write into TMR0, and
		 * + 1 for addition instruction
		 * So the resulting calculation is 250ticks * 0.4us = 100us (approx)
		 */
		TMR0 += 8;

		if (tmr0_hundred_usecs++ == 4)
		{
			tmr0_hundred_usecs = 0;

			if (update_clcd)
			{
				update_clcd_screen();
			}
		}

		if (tmr0_hundred_usecs_1++ == 8000)
		{
			tmr0_hundred_usecs_1 = 0;

			if(seconds++==59)
			{
				seconds = 0;
				if(minutes++==59)
				{
					minutes = 0;
					if(hours++==23)
					{
						hours = 0;
					}
				}
				
			}
		}

		T0IF = 0;
	}
}
