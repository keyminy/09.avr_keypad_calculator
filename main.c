/*
 * 04.TIMER_TEST.c
 *
 * Created: 2024-04-26 오후 3:23:34
 * Author : HARMAN-27
 */ 

#include "def.h"
#include "extern.h"
#include "queue.h"



//stidio.h에 file구조체가 들어있다
// 1. for printf
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit,NULL, _FDEV_SETUP_WRITE);

char scm[50];

int main(void)
{
	uint8_t keydata = 0;
	uint8_t readkey = 0;
	init_timer0();
	init_uart0();
	init_keypad();
	queue_init();
	
	stdout = &OUTPUT; // 2. printf가 동작되도록 stdout에 OUTPUT파일 포인터를 assign한다.
	// fprintf(stdout,"test"); == printf("test\n");
	// scanf("%s",buff); --> stdin
	// fgets(input,100,stdin); //여기서 stdin이 가리키는 것은 키보드입니다.
	
	//I2C_LCD_init(); // comportmaster로 검증하자.
	sei(); // 전역적으로 인터럽트를 허용하겠다
	
	//led A레지스터
	DDRA = 0xff; //출력모드 설정
	PORTA = 0x00; // led all off
	
	/* UART통신, main의 while문 진입전 테스트*/
	//printf("UART TEST!!!!\n");


	
    while (1) 
    {
		if(ms_count >= 60){
			ms_count = 0;
			if(keydata =scan_keypad()){
				insert_queue(keydata);
			}
		}
		if(queue_empty() != TRUE){
			readkey = read_queue();
			printf("readkey:%c\n",readkey);
		}
	}
}

