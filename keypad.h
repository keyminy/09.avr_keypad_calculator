/*
 * keypad.h
 *
 * Created: 2024-05-16 오전 11:01:02
 *  Author: HARMAN-27
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 16000000UL
#include <avr/io.h> // PORTA DDRA 등의 symbom이 정의 되어 있다.

#define KEYPAD_DDR DDRA
#define KEYPAD_PIN PINA // keypad입력값을 감지하기 위함
#define KEYPAD_PORT PORTA 

void init_keypad(void);

#endif /* KEYPAD_H_ */