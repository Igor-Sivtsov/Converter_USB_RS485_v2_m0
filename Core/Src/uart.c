#include "string.h"
#include "uart.h"

exchange rx = {}, tx = {};

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

void clear_obj(exchange *obj)
{
	memset(&obj->buf, 0, obj->buf_len);
	obj->buf_len = 0;
	obj->cnt = 0;
	obj->state = waiting;
}

void timeout_handler()
{
	clear_obj(&tx);
	clear_obj(&rx);

	start_uart_resive();
}
