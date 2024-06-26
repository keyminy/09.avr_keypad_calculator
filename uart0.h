﻿/*
 * uart0.h
 *
 * Created: 2024-05-16 오후 2:10:46
 *  Author: HARMAN-27
 */ 


#ifndef UART0_H_
#define UART0_H_
#include <stdint.h>
//uart0로 부터 들어온 문자를 저장하는 버퍼
//interrupt루틴에서 사용하는 변수는 최적화방지를위해 volatile키워드
// volatile uint8_t rx_buff[100];
//기본 : 0으로 set해줍니다
//volatile uint8_t rx_ready_flag = 0; // 완전한 문장(\n)을 만나면 1로 set된다.

volatile int input_index=0;   // ISR(USART0_RX_vect) 저장 하는 index
volatile int output_index=0;  // pc_command_processing에서 꺼내가는 index
volatile uint8_t rx_Quebuff[20][40];


void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(void);



#endif /* UART0_H_ */