/*	Author: dpere048
 *  Partner(s) Name: 
 *	Lab Section:021
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{START, LED0, LED1, WAIT} state;
unsigned char button;
unsigned char tmpA;
void Led_Tick(){
	switch(state){
	case START:
		if(button == 1){
		state = LED1;
		}
		else{
		state = START;
		}
		break;
	case LED0:
		if(button == 1){
		state = LED0;
		}
		else{
		state = START;
		}
		break;
	case LED1:
		if(button == 1){
		state = LED1;
		}
		else{
		state = WAIT;
		}
		break;
	case WAIT:
		if(button == 1){
		state = LED0;
		}
		else{
		state = WAIT;
		}
		break;
	}
	switch(state){
	case START:
		tmpA = 0x01; //PB0 is on
	break;
	case LED0:
		tmpA = 0x01; //PB0 is on
	break;
	case LED1:
		tmpA = 0x02; //PB1 is on
	break;
	case WAIT:
		tmpA = 0x02; //PB1 is on
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
	button = PINA&0x01;//PA0
	Led_Tick();
	PORTB = tmpA;
    }
    return 1;
}
