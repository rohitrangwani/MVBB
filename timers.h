#ifndef TIMERS_H
#define TIMERS_H

#define ENABLE_TIMER		T0IE = 1
#define DISABLE_TIMER		T0IE = 0

extern unsigned short tmr0_hundred_usecs;
extern unsigned short tmr0_hundred_msecs;

extern unsigned long tmr0_overflow;

void init_timer0(void);

#endif
