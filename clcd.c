#include "main.h"
#include "clcd.h"
#include "timers.h"

volatile unsigned char clcd_buff[NO_OF_LINES][CLCD_LINE_LEN] = 
{
	{0x80,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
	{0xC0,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',}
};

unsigned char data_offset, update_clcd;
static unsigned char lcd_cntl;

/* Just used write commands while Initialization of CLCD */
void write(unsigned char bit_value)
{
	unsigned char nibble;
	unsigned short wait;

	RS(LOW);

	for (nibble = 0; nibble < 2; nibble++)
	{
		LCD_PORT = (LCD_PORT & 0x0F) | ((bit_value << (4 * nibble)) & 0xF0);
		EN(1);
		for (wait = 1000; wait--; );
		EN(0);
	}
}

void init_clcd(void)
{
	/* Set PortD as output port */
	TRISD = 0x00;

	RW(LOW);

	STABILIZE_LCD;
	CURSOR_HOME;
	DISP_ON_AND_CURSOR_OFF;
	CLEAR_DISP_SCREEN;
}

int strlen(const unsigned char *str)
{
	int i = 0;

	while (*str++)
	{
		i++;
	}

	return i;
}

char *strncpy(unsigned char *dest, const unsigned char *src, int size)
{
	int i;

	for (i = 0; i < size && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	for ( ; i < size; i++)
	{
		dest[i] = '\0';
	}

	return dest;
}

void clcd_print(const unsigned char *data, unsigned char pos)
{
	unsigned char len;

	/* Adjust the pos value if it is in line 2 */
	pos = (pos < (CLCD_LINE_LEN - 1)) ? pos : pos + 1;

	/* Check whether requested string is not greater the stirng size*/ 
	len = ((strlen(data) + (pos % CLCD_LINE_LEN)) > CLCD_LINE_LEN - 1) ? (CLCD_LINE_LEN - 1) : strlen(data); 

	strncpy(clcd_buff[pos / CLCD_LINE_LEN] + (pos % CLCD_LINE_LEN) + 1, data, len);

	update_clcd = 1;
}

void clcd_putch(unsigned char data, unsigned char pos)
{
	/* Adjust the pos value if it is in line 2 */
	pos = (pos < (CLCD_LINE_LEN - 1)) ? pos : pos + 1;

	clcd_buff[pos / CLCD_LINE_LEN][(pos % CLCD_LINE_LEN) + 1] = data;

	update_clcd = 1;
}

/* This function is to be called in Timer ISR */
void update_clcd_screen(void)
{
	static unsigned char data = 0;
	static unsigned char nibble = 0;

	/* Start pushing the data on port only when the enable line is Low */
	if(EN_PIN_LOW)
	{
		/* The below line is to change the line to be printed on CLCD */
		/* The clcd_buff containes the line addresses of the CLCD on start */
		RS(!!(data_offset % CLCD_LINE_LEN));

		data =  clcd_buff[data_offset / CLCD_LINE_LEN][data_offset % CLCD_LINE_LEN];
		/* Send char data to the LCD */
		if (nibble)
		{
			/* LSB nibble */
			if ((data_offset + 1) < (NO_OF_LINES * CLCD_LINE_LEN))
			{
				data_offset += 1;
			}
			else
			{
				/* Screen updated so no need of refreshing again */
				update_clcd = 0;
				data_offset = 0;
			}
			LCD_PORT = (LCD_PORT & 0x0F) | ((data << 4)  & 0xF0);
		}
		else
		{
			LCD_PORT = (LCD_PORT & 0x0F) | (data  & 0xF0);
		}
		nibble = !nibble;
	}
	/* Once the data is on port, Enable the CLCD to process the data */
	/* This line also makes sure that is enable pulse generated for two overflows */
	EN(PIN_TOGGLE);
}
