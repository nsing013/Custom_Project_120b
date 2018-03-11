#include <avr/io.h>
#include "nokia5110.h"
#include "nokia5110.c"

int level = 0;
int score = 0;
short button;

enum Nokia_LCD_States {Nokia_LCD_Start, Nokia_LCD_wait_before_level, Nokia_LCD_levels, Nokia_LCD_Continue} Nokia_LCD_State;
void nokia_LCD_tick() 
{													
	button = ~PINB & 0x20;											//checking for button press to move on to levels button press 
	switch(Nokia_LCD_State)	//transitions
	{	
		case Nokia_LCD_Start:										//starting stuff
			nokia_lcd_init();
			nokia_lcd_power(1);
			nokia_lcd_set_cursor(0, 0);
			nokia_lcd_write_string("MEMORY", 2);
			nokia_lcd_render();
			nokia_lcd_set_cursor(0, 18);
			nokia_lcd_write_string("Press button to continue.", 1);	//want this to display until user gives input
			nokia_lcd_render();
			Nokia_LCD_State = Nokia_LCD_wait_before_level;						//go to the wait state and wait for input from button
			break;
		
		case Nokia_LCD_wait_before_level:
			if(button)	//in the wait state if the user presses the joystick continue to level 1
			{
				nokia_lcd_clear();	//clear the screen
				Nokia_LCD_State = Nokia_LCD_levels;
			}
			else
			{
				Nokia_LCD_State =  Nokia_LCD_wait_before_level; //loop in wait state until user presses something
			}
			break;

		case Nokia_LCD_levels:
			level++;			//want level to be 1 the first time and increment every time it comes to level state
			nokia_lcd_set_cursor(0, 0);
			nokia_lcd_write_string("Level: ", 1); //display the level number!!! HELP
			nokia_lcd_render();
			nokia_lcd_write_string("Score: ", 1); //display the score!!! HELP
			nokia_lcd_render();
			//display the level image on the matrix for 10 seconds! HELP!
			
			//each level has a different picture which will display on the LED Matrix. 
			// so depending on the level send output to the matrix state machine.
			Nokia_LCD_State =  Nokia_LCD_Continue;
			break;
		case Nokia_LCD_Continue:
			break;
		default:
			Nokia_LCD_State = Nokia_LCD_Start;
			break;
	} //end of the transitions
	
	switch(Nokia_LCD_State) //state actions for what happens for the buttons below this
	{
		case Nokia_LCD_Start:
			break;
		case Nokia_LCD_wait_before_level:
			break;
		case Nokia_LCD_levels:
			break;
		case Nokia_LCD_Continue:
			break;
		default:
			break;
	}
	
	//PORTC = output;
} //end of Button LA function