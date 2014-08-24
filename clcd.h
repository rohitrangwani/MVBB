#ifndef LCD_H
#define LCD_H

#define LCD_PORT										PORTD
#define BL(x)											LCD_PORT = (LCD_PORT & 0b11111110) | (0b00000001 & (x << 0))
#define RW(x)											LCD_PORT = (LCD_PORT & 0b11111011) | (0b00000100 & (x << 2))
#define RS(x)											LCD_PORT = (LCD_PORT & 0b11111101) | (0b00000010 & (x << 1))
#define EN(x)											LCD_PORT = (LCD_PORT & 0b11111110) | (0b00000001 & (x << 0))

#define EN_PIN											RD0
#define EN_PIN_LOW										!EN_PIN
#define PIN_TOGGLE										EN_PIN = !EN_PIN

#define LOW												0
#define HIGH											1

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0

#define LINE1(x)										(0 + (x))
#define LINE2(x)										(16 + (x))

#define LEFT_ARROW										0x7F
#define RIGHT_ARROW										0x7E

#define ONE_LINE_5x7_MATRIX_8_BIT						write(0x30)
#define TWO_LINE_5x10_MATRIX_8_BIT						write(0x3C)
#define TWO_LINE_5x7_MATRIX_4_BIT						write(0x28)
#define TWO_LINE_5x10_MATRIX_4_BIT						write(0x2C)

#define	STABILIZE_LCD									write(0x33)

#define MOV_CURSOR_TO_LINE1								write(0x80)
#define MOV_CURSOR_ADDR(address)						write(address)
#define MOV_CURSOR_TO_LINE2								write(0xC0)
#define MOV_CURSOR_ADDR(address)						write(address)

#define CLEAR_DISP_SCREEN								write(0x01)
#define CLEAR_DISP_WITH_DELAY(delay)					write(0x01)
#define CURSOR_HOME										write(0x02)

#define DISP_OFF_AND_CURSOR_OFF							write(0x08)
#define DISP_OFF_AND_CURSOR_ON							write(0x0A)
#define DISP_ON_AND_CURSOR_ON							write(0x0E)
#define DISP_ON_AND_CURSOR_OFF							write(0x0C)
#define DISP_ON_AND_CURSOR_BILNK_OFF					write(0x0E)
#define DISP_ON_AND_CURSOR_BILNK_ON						write(0x0F)

#define SHIFT_CURSOR_LEFT_WITH_DELAY(delay)				write(0x04)
#define SHIFT_CURSOR_RIGHT_WITH_DELAY(delay)			write(0x07)
#define SHIFT_CURSOR_POS_LEFT_WITH_DELAY(delay)			write(0x10)
#define SHIFT_CURSOR_POS_RIGHT_WITH_DELAY(delay)		write(0x14)
#define SHIFT_DISPLAY_LEFT_WITH_DELAY(delay)			write(0x07)
#define SHIFT_DISPLAY_RIGHT_WITH_DELAY(delay)			write(0x05)
#define SHIFT_ENTIRE_DISPLAY_LEFT_WITH_DELAY(delay)		write(0x18)
#define SHIFT_ENTIRE_DISPLAY_RIGHT_WITH_DELAY(delay)	write(0x1C)

/* 
 * Max 16 char we can print per line and at begining of line we are storing 
 * Command for pertiqular line number
 */
#define CLCD_LINE_LEN									17 /* (16 + 1)*/
#define NO_OF_LINES										2

extern unsigned char data_offset, update_clcd;
extern unsigned char clcd_buff[NO_OF_LINES][CLCD_LINE_LEN]; 

void init_clcd(void);
void clcd_print(const char *data, unsigned char pos);
void clcd_putch(unsigned char data, unsigned char pos);
void update_clcd_screen(void);

#endif
