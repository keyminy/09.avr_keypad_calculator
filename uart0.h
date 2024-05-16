#ifndef UART0_H_
#define UART0_H_
#include <stdint.h>

volatile uint8_t rx_buff[100];
volatile uint8_t rx_ready_flag = 0;

void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(void);

#endif /* UART0_H_ */