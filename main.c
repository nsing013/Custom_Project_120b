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
	//start code for testing JOYSTICK
	unsigned short valueX, valueY;
	unsigned short idle = 543;
	unsigned short left_threshold = 250; 
	unsigned short right_threshold = 820;
	
	//PA[0] connected to potentiometer giving input //LEFT and RIGHT for joystick right now
	//PA[1] want to connect to  y axis
	
	DDRA = 0x00; PORTA = 0xFF; //input from joystick	
	DDRB = 0x1F; PORTB = 0xE0; //output to the LCD //one input from button
	DDRC = 0xFF; PORTC = 0x00; //Pattern on each row of LED Matrix
	DDRD = 0xFF; PORTD = 0x00; //Row # 
   
	short button = ~PINB & 0x20;
	
	if(button)
	{
		nokia_lcd_init();
		nokia_lcd_power(1);
		nokia_lcd_set_cursor(0, 0);
		nokia_lcd_write_string("Button is pressed!", 1); //only want this to display for 5 seconds
		nokia_lcd_render();
	}
	
	ADC_init();
	char snum[10]; //Char array holds ADC Value to display on LCD
	
	TimerSet(100);
	TimerOn();
	
	while(1)
	{
		//LED_Matrix_Tick(LED_Matrix_levels);
		//nokia_LCD_tick(Nokia_LCD_Start);
		valueX = Read_ADC(1);
		valueY = Read_ADC(0);
		
		/* Testing ADC Value on LCD Screen */
		/*
		itoa(valueY, snum, 10);
		nokia_lcd_init();
		nokia_lcd_power(1);
		nokia_lcd_set_cursor(0, 0);
		nokia_lcd_write_string(snum, 1);
		nokia_lcd_render();
		*/
		/* End Testing ADC Value */
		
		LED_Matrix_Tick(LED_Matrix_cursor);				//LED MATRIX STATE MACHINE		
		
		if(valueX < left_threshold)						//joystick is in the left position
		{
			LED_Matrix_Tick(LED_Matrix_move_left);		//decrement x value on cursor
		}
		
		if(valueX > right_threshold)					//joystick is in the right position
		{
			LED_Matrix_Tick(LED_Matrix_move_right);		//increment x value on cursor
		}
		
		if(valueY < left_threshold)						//joystick is in the left position
		{
			LED_Matrix_Tick(LED_Matrix_move_down);		//decrement x value on cursor
		}
		
		if(valueY > right_threshold)					//joystick is in the right position
		{
			LED_Matrix_Tick(LED_Matrix_move_up);		//increment x value on cursor
		}
		while(!TimerFlag);
		TimerFlag = 0;
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