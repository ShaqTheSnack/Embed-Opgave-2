#include "../../include/ProjectDefines.h"
#include "../../include/uart/uart.h"

void ConvertReceivedChar(char *ReceivedChar)
{
    if ((*ReceivedChar >= 'a') && (*ReceivedChar <= 'z'))
    {
        *ReceivedChar = *ReceivedChar - 32;
    }
    else if ((*ReceivedChar >= 'A') && (*ReceivedChar <= 'Z'))
    {
        *ReceivedChar = *ReceivedChar + 32;
    }
}

void UART0_Init(void)
{
    UBRR0L = (unsigned char)(MyUBRR & 0xff);
    UBRR0H = (unsigned char)(MyUBRR >> 8);
#ifdef UART_NORMAL_MODE
    UCSR0A = 0x00;
#else
    UCSR0A = 1 << U2X0;
#endif
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART1_Init(void)
{
    UBRR1L = (unsigned char)(MyUBRR & 0xff);
    UBRR1H = (unsigned char)(MyUBRR >> 8);
#ifdef UART_NORMAL_MODE
    UCSR1A = 0x00;
#else
    UCSR1A = 1 << U2X1;
#endif
    UCSR1B = (1 << RXEN1) | (1 << TXEN1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void Enable_UART_Receive_Interrupt(void) { UCSR0B |= (1 << RXCIE0); }

void UART0_WriteChar(char ch)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ch;
}

void UART1_WriteChar(char ch)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = ch;
}

void UART1_WriteString(const char *text)
{
    while (*text != '\0')
    {
        UART1_WriteChar(*text);
        text++;
    }
}

ISR(USART0_RX_vect)
{
    char ReceivedByte = UDR0;

    ConvertReceivedChar(&ReceivedByte);

    UART0_WriteChar(ReceivedByte);
    UART1_WriteChar(ReceivedByte);
}
