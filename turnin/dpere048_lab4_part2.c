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
enum States{START, UP, DOWN, ZERO, WAIT, WAIT2} state;
unsigned char buttonA0;
unsigned char buttonA1;
unsigned char tmpA;
void Button_Tick(){
	switch(state){
		case START:
			if(!buttonA1 && !buttonA0){
			state = START; //no action taken, portc = 7
			}
			else if(!buttonA1 && buttonA0){
			state = UP; //incremented
			}
			else if(!buttonA0 && buttonA1){
			state = DOWN; //decremetned
			}
			else if(buttonA0 && buttonA1){	
			state = ZERO; //both pressed togetehr 
			}
		break;
		case UP:
			if(buttonA0 && buttonA1){
			state = ZERO;
			}
			else{
			state = WAIT;
			}
		break;
		case DOWN:
			if(buttonA0 && buttonA1){
			state = ZERO;
			}
			else{
			state = WAIT2;
			}
		break;
		case ZERO:
			if(!buttonA0 && !buttonA1){
			state = START;
			}
			else if(buttonA0 && !buttonA1){
			state = UP;
			}
			else if(buttonA1 && !buttonA0){
			state = DOWN;
			}
			else if(buttonA0 && buttonA1){
			state = ZERO;
			}
		break;
		case WAIT:
			if(buttonA0 && buttonA1){
			state = ZERO;
			}
			else if(!buttonA0 && !buttonA1){
			state = WAIT2;
			}
			else{
			state = WAIT;
			}		
		break;
		case WAIT2:
			if(buttonA0 && buttonA1){
			state = ZERO;
			}
			else if(buttonA0 && !buttonA1){
			state = UP;
			}
			else if(buttonA1 && !buttonA0){
			state = DOWN;
			}
			else{
			state = WAIT;
			}
		break;
	}
	switch(state){
                case START:
                break;
                case UP:
			if(tmpA < 9){
			tmpA = tmpA +1;
			}
                break;
                case DOWN:
			if(tmpA > 0){
			tmpA = tmpA -1;
			}
                break;
                case ZERO:
			tmpA = 0;
                break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF;
DDRC = 0xFF; PORTC = 0x00;
state = START;
tmpA = 0x07;
    /* Insert your solution below */
    while (1) {
	buttonA0 = PINA&0x01;
	buttonA1 = PINA&0x02;
	Button_Tick();
	PORTC = tmpA;
    }
    return 1;
}
