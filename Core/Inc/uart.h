#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

typedef enum
{
	waiting,
	in_progress,
	completed
}  	state;

struct exchange
{
	uint8_t		buf[1000];
	size_t 		buf_len;
	uint16_t	cnt;
	state 		state;
};

void start_uart_resive();
void start_uart_transmit();

#endif /* INC_UART_H_ */
