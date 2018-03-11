/*
 * Custom_Projects_YAAAAS.c
 * Created: 3/4/2018 8:30:52 PM
 * Author : Nikita
 */ 

#include <avr/io.h>
#include "timer.h"
#include "nokia_LCD.c"
#include "LED_Matrix.c"
#include "joystick.c"

int main(void)
{

	//PA[0] connected to potentiometer giving input //LEFT and RIGHT for joystick right now
	//PA[1] want to connect to  y axis
	
	DDRA = 0x00; PORTA = 0xFF; //input from joystick
	DDRB = 0x1F; PORTB = 0xE0; //output to the LCD //one input from button
	DDRC = 0xFF; PORTC = 0x00; //Pattern on each row of LED Matrix
	DDRD = 0xFF; PORTD = 0x00; //Row # 

	ADC_init();
	char snum[10]; //Char array holds ADC Value to display on LCD
	
	TimerSet(10); //30);
	TimerOn();	
	
	while(1)
	{
		//LED_Matrix_Tick(LED_Matrix_levels);
		nokia_LCD_tick(Nokia_LCD_Start);
		while(!TimerFlag)
			LED_Matrix_Tick(LED_Matrix_cursor);				//LED MATRIX STATE MACHINE
			
		Joystick_tick(Joystick_navigate);
		TimerFlag = 0;	
	}
}