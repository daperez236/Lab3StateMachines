/*	Author: dpere048
 *  Partner(s) Name: 
 *	Lab Section:021
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{START, WAIT, UNLOCK, WAIT2} state;
unsigned char buttonX;
unsigned char buttonY;
unsigned char buttonM;
unsigned char buttonLOCK; //locks house
unsigned char tmpA;
void Lock_Tick(){
buttonX = PINA&0x01;
buttonY = PINA&0x02;
buttonM = PINA&0x04;
buttonLOCK = PINA&0x80; 
	switch(state){
	case START:
		if(buttonLOCK){
		state = START;
		}
		else if(!buttonX && !buttonY && buttonM &&!buttonLOCK){
		state = WAIT;
		}
		else{
		state = START;
		}	
	break;
	case WAIT:
		if(!buttonX && !buttonY && buttonM && !buttonLOCK){
		state = WAIT; //button is held down
		}
		else if(!buttonX && !buttonY && !buttonM && !buttonLOCK){
		state = WAIT2;
		}
		else{
		state = START;
		}
	break;
	case UNLOCK:
		if(!buttonX && !buttonY && !buttonM && buttonLOCK){
		state = START;
		}
		else{
		state = UNLOCK;
		}
	break;
	case WAIT2:
		if(!buttonX && !buttonY && !buttonM && !buttonLOCK){
		state = WAIT2; //wait for button press
		}
		else if(!buttonX && buttonY && !buttonM && !buttonLOCK){
		state = UNLOCK;
		}
		else{
		state = START; //any other input locks
		}
	break;
	}
	switch(state){
	case START:
	tmpA = 0x00;
	break;
	case WAIT:
	break;
	case UNLOCK:
	tmpA = 0x01; //PB0
	break;
	case WAIT2:
	break;
	}
	
}
int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
state = START;
    /* Insert your solution below */
    while (1) {
	Lock_Tick();
	PORTB = tmpA;
    }
    return 1;
}
