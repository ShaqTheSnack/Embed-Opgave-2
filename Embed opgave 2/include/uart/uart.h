#ifndef UART_H_
#define UART_H_

#include "../../include/ProjectDefines.h"

#define BAUD 9600UL

#define UART_NORMAL_MODE
#ifdef UART_NORMAL_MODE
#define MyUBRR (unsigned int)(F_CPU / (16 * BAUD) - 1)
#else
#define MyUBRR (unsigned int)(F_CPU / (8 * BAUD) - 1)
#endif

extern void ConvertReceivedChar(char *ReceivedChar);
extern void UART0_Init(void);
extern void UART1_Init(void);
extern void UART0_WriteChar(char ch);
extern void UART1_WriteChar(char ch);
extern void UART1_WriteString(const char *text);
extern void Enable_UART_Receive_Interrupt(void);

#endif
