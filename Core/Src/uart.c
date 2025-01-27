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
	USART3->CR1 |=  USART_CR1_TE;

	TX_EN_GPIO_Port->BSRR = TX_EN_Pin;

	USART3->TDR = tx.buf[tx.cnt++];
}

void clear_obj(exchange *obj)
{
	memset(&obj->buf, 0, obj->buf_len);
	obj->buf_len = 0;
	obj->cnt 	 = 0;
	obj->state   = waiting;
}

void reset_state()
{
	memset(&tx, 0, sizeof(tx));
	memset(&rx, 0, sizeof(rx));

	uart_error_handler();
}

inline void uart_error_handler()
{
	if(USART3->ISR & USART_ISR_PE)	USART3->ICR |= USART_ICR_PECF;
	if(USART3->ISR & USART_ISR_FE)	USART3->ICR |= USART_ICR_FECF;
	if(USART3->ISR & USART_ISR_NE)	USART3->ICR |= USART_ICR_NCF;
	if(USART3->ISR & USART_ISR_ORE)	USART3->ICR |= USART_ICR_ORECF;
}
