#include "keypad.h"

void init_keypad();
uint8_t scan_keypad();
uint8_t get_keypad(int row,int col);

void init_keypad(void){
	KEYPAD_DDR = 0xf0;
	KEYPAD_PORT = 0xff;
}

// Returns the pressed keypad value.
// 주기적으로 호출한다(scanning방식). 약 60ms마다 호출함
uint8_t scan_keypad(){
	uint8_t data = 0; // key값을 저장할 변수
	for(int row = 3; row >= 0; row--){
		for(int col = 0; col < 4; col++){
			data = get_keypad(row,col);
			if(data){ // if (data >= 1)
				return data;
			}
		}
	}
}

uint8_t get_keypad(int row,int col)
{
	// make keypad mapping table
	uint8_t keypad_char[4][4] = {
		{' ','0','=','+'},
		{'4','5','6','*'},
		{'7','8','9','-'},
		{'1','2','3','/'}
	};
	// To prevent keypad button chattering
	// Since it is active low, we set the initial value to 1. 
	// '1' is key is not pressed
	static uint8_t prev_keystate[4][4] = {
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1}
	};
	int current_state = 1; // button initial value to 1
	
	KEYPAD_PORT = 0xff;
	KEYPAD_PORT &= ~(1 << col + 4); // 해당 col에 전류를 흘린다.
	// 해당 keypad port의 column값을 LOW로 만든다.
	
	// 반드시 아래의 코드를 집어 넣는다(To prevent chattering)
	for(int delay=0; delay < 20; delay++); // NOP no operation
	// keypad check delay
	
	// 7  6  5  4   3   2  1  0
	//C4 C3 C2 C1   R0 R1 R2 R3
	//ex) row0 : connected to PA3
	// if row0 is pressed
	// 1  1 1  1    0  1  1  1 // if you pressed the button, values goes to 0
	// 0  0 0  1    1  1  1  0(important)   (After shifting)
	// & 0b00000001;하면?
	// 0  0 0  0    0  0  0  x 가됨 -> 현재 current_state
	//current_state = ((KEYPAD_PIN & (1 << row-3))) >> (row-3)) & 0b00000001;
	current_state = KEYPAD_PIN >> row & 0b00000001; //row : 3이들어오면 0행의 row를 읽는 것
	// 눌려졌다?
	
	// current_state == 0이면 버튼이 눌러진 상태(pull up이기 때문에 active시 LOW)
	// 1.처음 버튼이 눌러진 상태인가?
	if(current_state == 0 && prev_keystate[col][row] == 1){
		// 처음 버튼이 눌려진 상태
		prev_keystate[col][row] = 0;
		return 0; // 버튼이 눌려진 상태이나 완전한 상태로 보지않고,
		// prev_keystate[col][row]만 눌려진 상태로 set한다.
	} //이전에 버튼이 눌려졌고(prev_keystate[col][row] == 0) 현재는 버튼을 뗀 상태(current_state == 1)
	else if(current_state == 1 && prev_keystate[col][row] == 0){
		// 다음 버튼상태 체크를 위해서 초기화 시켜준다
		prev_keystate[col][row] = 1;
		printf("key:%c\n",keypad_char[col][row]);
		return (keypad_char[col][row]); // key값을 리턴 
	}
	return 0; //이도저도 아닌 상태
}