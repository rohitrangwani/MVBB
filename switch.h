#ifndef SWITCH_H
#define SWITCH_H

#define INPUT_PINS			0x3F
#define DEFAULT_INPUT_LEVEL	0x3F

#define DIRECTION_REGISTER	TRISB
#define PORT				PORTB

#define SET_INPUTS			DIRECTION_REGISTER |= INPUT_PINS
#define RESET_INPUTS		DIRECTION_REGISTER &= ~INPUT_PINS

#define DETECT_STATE		detection_type == 1
#define CONTINUOUS			detection_type == 0

#define STATE				1
#define LEVEL				0

/* Enable this if you want to read state transition in pull up config*/
/* Enable this if you want to read level transition in pull down config*/
#if 1 
#define SWITCH1			0x01
#define SWITCH2			0x02
#define SWITCH3			0x04
#define SWITCH4			0x08
#define SWITCH5			0x10
#define SWITCH6			0x20
/* Enable this if you want to read state transition in pull up config*/
#else 
#define SWITCH1			0x3E
#define SWITCH2			0x3D
#define SWITCH3			0x3B
#define SWITCH4			0x37
#define SWITCH5			0x1F
#define SWITCH6			0x2F
#endif

unsigned char read_switches(unsigned char detection_type);

#endif
