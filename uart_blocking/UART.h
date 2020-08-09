#ifndef UART_H
#define UART_H



void USART_config(unsigned int ubrr);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);

#endif