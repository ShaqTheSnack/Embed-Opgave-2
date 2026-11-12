#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

extern volatile uint8_t Timer1ElapsedFlag;
extern void Timer1_Init_ms(uint16_t timeout_ms);

#endif
