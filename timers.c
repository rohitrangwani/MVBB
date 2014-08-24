#include "main.h"

unsigned short tmr0_hundred_usecs;
unsigned short tmr0_hundred_msecs;

unsigned long tmr0_overflow;

void init_timer0(void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */
	T0CS = 0;
	/* Assigning prescaler to timer0 */
	PSA = 0;
	/*
	 * We will set prescaler value of 2 to achieve 400ns with 200ns
	 * instruction cycle, i.e. increment counter every 400ns and hence
	 * generate interrupt after 102.8us, but we need 100us, so
	 * starting from 8, i.e. a value of 6, and
	 * + 1 for extra cycles, caused by write into TMR0, and
	 * + 1 for addition instruction
	 */
	TMR0 = 8;
	/* Setting the prescaler to 2 */
	PS2 = 0;
	PS1 = 0;
	PS0 = 0;
	/* Clearing timer0 overflow interrupt flag bit */
	T0IF = 0;
	/* Initialize the variables for the interrupt handler */
	tmr0_overflow = 0;
	tmr0_hundred_usecs = 0;
	tmr0_hundred_msecs = 0;
	/* Enaling timer0 overflow interrupt */
	T0IE = 1;
}
