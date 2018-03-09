#include <avr/io.h>
#include "nokia5110.h"
#include "nokia5110.c"

enum Nokia_LCD_States {Nokia_LCD_Start, Nokia_LCD_wait, Nokia_LCD_levels} Nokia_LCD_State;

void nokia_LCD_tick() 
{
	int level = 0;
	//button = ~PINA & 0x03;
	switch(Nokia_LCD_State) //start transitions that take place between the states
	{	
		case Nokia_LCD_Start:
			nokia_lcd_init();
			nokia_lcd_power(1);
			nokia_lcd_set_cursor(0, 0);
			nokia_lcd_write_string("MEMORY", 2); //only want this to display for 5 seconds
			nokia_lcd_render();
			nokia_lcd_set_cursor(0, 18);
			nokia_lcd_write_string("Do you want to continue?", 1); //want this to display until user gives input
			nokia_lcd_render();
			//Nokia_LCD_State = Nokia_LCD_wait;
			break;
		
		case Nokia_LCD_wait:
			//in the wait state if the user presses the joystick continue to level 1
			//if (button == 0x01) //joystick input
			{
				level++; //want level to be 1 the first time and increment every time it comes to wait state
				Nokia_LCD_State = Nokia_LCD_levels;
			}
			//else
			{
				Nokia_LCD_State =  Nokia_LCD_wait; //loop in wait state until user presses something
			}
			break;

		case Nokia_LCD_levels:
			//each level has a different picture which will display on the LED Matrix. 
			// so depending on the level send output to the matrix state machine.
			break;
				
		default:
			Nokia_LCD_State = Nokia_LCD_Start;
			break;
	} //end of the transitions
	
	switch(Nokia_LCD_State) //state actions for what happens for the buttons below this
	{
		case Nokia_LCD_Start:
			break;
		case Nokia_LCD_wait:
			break;
		case Nokia_LCD_levels:
			break;
		default:
			break;
	}// end of the state actions
	
	//PORTC = output;
} //end of Button LA function