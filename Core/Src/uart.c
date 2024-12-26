#include "uart.h"

struct exchange rx = {}, tx = {};

void start_uart_resive()
{
	TX_EN_GPIO_Port->BSRR = TX_EN_Pin << 16;
	USART3->CR1 |= USART_CR1_RE;
}

void start_uart_transmit()
{
	USART3->CR1 &= ~USART_CR1_RE;
	TX_EN_GPIO_Port->BSRR = TX_EN_Pin;
	USART3->CR1 |= USART_CR1_TE;
	USART3->TDR = tx.buf[tx.cnt++];
}
