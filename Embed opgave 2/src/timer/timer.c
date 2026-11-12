#include "../../include/ProjectDefines.h"
#include "../../include/timer/timer.h"

volatile uint8_t Timer1ElapsedFlag = 0;

void Timer1_Init_ms(uint16_t timeout_ms)
{
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    TCCR1B |= (1 << WGM12);

    TCCR1B |= (1 << CS12);

    uint32_t ticks = ((F_CPU / 256UL) * timeout_ms) / 1000UL;

    if (ticks > 0)
    {
        ticks--;
    }

    if (ticks > 65535)
    {
        ticks = 65535;
    }

    OCR1A = (uint16_t)ticks;

    TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << GreenLedBit) | (1 << YellowLedBit);
    Timer1ElapsedFlag = 1;
}
