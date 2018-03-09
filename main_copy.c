/*
 * Custom_Projects_YAAAAS.c
 * Created: 3/4/2018 8:30:52 PM
 * Author : Nikita
 */ 

#include <avr/io.h>
#include "timer.h"
#include "nokia_LCD.c"
#include "LED_Matrix.c"
//#include "joystick.c"


void ADC_init() // Using ADC to get the x and y axis of the JOYSTICK
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
		// ADEN: setting this bit enables analog-to-digital conversion.
		// ADSC: setting this bit starts the first conversion.
		// ADATE: setting this bit enables auto-triggering. Since we are in Free Running Mode, a new conversion will trigger whenever the previous conversion completes.
	//ADMUX = 0x41; //alternates between A0 and A1 which are the horizontal and vertical values on the joystick // &=E0
}

unsigned short Read_ADC(uint8_t ch) 
{
	ADMUX = (1<<REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2);
	ch = ch&0x07;
	ADMUX |= ch; //alternates between A0 and A1 which are the horizontal and vertical values on the joystick // &=E0
	
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA |= (1<<ADIF);
	return ADC;
}


int main(void)
{
	//start code for testing JOYSTICK
	unsigned short valueX, valueY;
	unsigned short idle = 543;
	unsigned short left_threshold = 250; 
	unsigned short right_threshold = 820;
	
	//PA[0] connected to potentiometer giving input //LEFT and RIGHT for joystick right now
	//PA[1] want to connect to  y axis
	DDRA = 0x00; PORTA = 0xFF; //input from joystick	
	DDRB = 0xFF; PORTB = 0x00; //output to the LCD
	DDRC = 0xFF; PORTC = 0x00; //Pattern on each row of LED Matrix
	DDRD = 0xFF; PORTD = 0x00; //Row #
   
	ADC_init();
	char snum[10]; //Char array holds ADC Value to display on LCD
	
	//TimerSet(100);
	//TimerOn();
	
	while(1)
	{
		valueX = Read_ADC(1);
		valueY = Read_ADC(0);
		
		/* Testing ADC Value on LCD Screen */
		itoa(valueY, snum, 10);
		nokia_lcd_init();
		nokia_lcd_power(1);
		nokia_lcd_set_cursor(0, 0);
		nokia_lcd_write_string(snum, 1);
		nokia_lcd_render();
		
		LED_Matrix_Tick(LED_Matrix_cursor);				//LED MATRIX STATE MACHINE		
		if(valueX < left_threshold)						//joystick is in the left position
		{
			LED_Matrix_Tick(LED_Matrix_move_left);		//decrement x value on cursor
		}
		
		if(valueX > right_threshold)						//joystick is in the right position
		{
			LED_Matrix_Tick(LED_Matrix_move_right);		//increment x value on cursor
		}
		
		if(valueY < left_threshold)						//joystick is in the left position
		{
			LED_Matrix_Tick(LED_Matrix_move_down);		//decrement x value on cursor
		}
		
		if(valueY > right_threshold)						//joystick is in the right position
		{
			LED_Matrix_Tick(LED_Matrix_move_up);		//increment x value on cursor
		}
		//while(!TimerFlag);
		//TimerFlag = 0;
	}
	//end code for testing JOYSTICK
	
	
	/*
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;  
	
	//TimerSet(1);
	//TimerOn();
	
	//SWITCH ALL THE GREEN WIRES BACKWARDS thats why its not working...
	//ALSO USING PORT C INSTEAD OF B SO BE CAREFUL
	
	while(1)
	{
		LED_Matrix_Tick(LED_Matrix_cursor);
		//while(!TimerFlag);
		//TimerFlag = 0;
	}
	*/
	
}