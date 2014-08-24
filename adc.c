#include "main.h"
#include "adc.h"

void init_adc(void)
{
	/* Right-justified digital value */
	ADFM = 1;

	/*
	 * Selecting the conversion clock of Fosc / 8, for max device frequency of 5MHz
	 * Our device frequency is 20 MHz
	 */
	ADCS0 = 0;
	ADCS1 = 1;

	/* Stop the conversion to start with */
	GO_DONE = 0;
	/* Turn on the module */
	ADON = 1;

	/* Voltage reference bit as VSS */
	VCFG1 = 0;
	/* Voltage reference bit as VDD */
	VCFG0 = 0;

	/* Setting all line as Analog Inputs */
	ANSEL = 0xFF;
	ANSELH = 0xFF;	

	/* Just clearing the ADRESH & ADRESL registers, for time pass */
	ADRESH = 0;
	ADRESL = 0;

	/* Reset Interrupt Enable Bit for polling*/
	ADIE = 0;
	/* Clear Interrupt Flag */
	ADIF = 0;
}

unsigned short get_voltage(unsigned char channel)
{
	unsigned char wait;
	unsigned short reg_val;

	/* Set the required channel */
	ADCON0 = (ADCON0 & 0xC3) | (channel << 2);

	/* A Small delay to satisfy the acqusition time after changing the channel. Refer datasheet for exact timing */
	for (wait = 100; wait--; );

	/* Start the conversion */
	GO_DONE = 1;
	while (GO_DONE);
	reg_val = (ADRESH << 8) | ADRESL; 

	return reg_val;
}
