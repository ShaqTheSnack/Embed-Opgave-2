#include <stdio.h>

#include "include/ProjectDefines.h"
#include "include/timer/timer.h"
#include "include/uart/uart.h"

int main(void)
{
    unsigned long seconds_after_start = 1200;
    char seconds_message[40];

    DDRB |= (1 << GreenLedBit) | (1 << YellowLedBit);

    Timer1_Init_ms(1000);

    UART0_Init();
    UART1_Init();

    Enable_UART_Receive_Interrupt();

    sei();

    while (1)
    {
        if (Timer1ElapsedFlag == 1)
        {
            Timer1ElapsedFlag = 0;
            seconds_after_start++;
            sprintf(seconds_message,
                    "Sekunder efter opstart: %lu\r\n",
                    seconds_after_start);
            UART1_WriteString(seconds_message);
        }
    }
}
