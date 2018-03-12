#include <avr/io.h>
#include "nokia5110.h"
#include "nokia5110.c"
//#include "LED_Matrix.c"


#ifndef __NOKIA_LCD_c__
#define __NOKIA_LCD_c__

char current_row = 0;
char level = 0;
char score = 0;
char row_is_correct = 0;
long LCD_counter;
short button;


void LCD_display(int l, char s)
{
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("Level: ", 1); //display the level number!!! HELP
	nokia_lcd_write_char((l + 48), 1);
	nokia_lcd_render();
	nokia_lcd_set_cursor(0, 18);
	nokia_lcd_write_string("Score: ", 1); //display the score!!! HELP
	nokia_lcd_write_char((s + 48), 1);
	nokia_lcd_render();
	return;
}

enum Nokia_LCD_States {Nokia_LCD_Start, Nokia_LCD_wait_before_level, Nokia_LCD_levels, Nokia_LCD_Compare, Nokia_LCD_Continue} Nokia_LCD_State;
void nokia_LCD_tick() 
{					
	char countdown;			
	char snum[10];					
	button = ~PINB & 0x20;											//checking for button press to move on to levels button press 
	switch(Nokia_LCD_State)	//transitions
	{	
		case Nokia_LCD_Start:													//starting stuff
			nokia_lcd_init();
			nokia_lcd_power(1);
			nokia_lcd_set_cursor(0, 0);
			nokia_lcd_write_string("MEMORY", 2);
			nokia_lcd_render();
			nokia_lcd_set_cursor(0, 18);
			nokia_lcd_write_string("Press button to continue.", 1);				
			nokia_lcd_render();													//want this to display until user gives input
			Nokia_LCD_State = Nokia_LCD_wait_before_level;						//go to the wait state and wait for input from button
			break;
			
		case Nokia_LCD_wait_before_level:										//loop in wait state until user presses something
			if(button)															//in the wait state if the user presses the joystick continue to level 1
			{
				nokia_lcd_clear();												//clear the screen
				level++;														//level turns to 1 first time
				Nokia_LCD_State = Nokia_LCD_levels;
			}
			break;

		case Nokia_LCD_levels:
			while(LCD_counter < 100000)											//10,000 ms is 10 seconds 10 second system period
			{
				LED_Matrix_Tick(LED_Matrix_levels);								//go to levels state for 10 seconds
				LCD_counter++;
			}
			LCD_counter = 0;
			Nokia_LCD_State =  Nokia_LCD_Continue; 
			break;

		case Nokia_LCD_Continue:
			while(LCD_counter < 30000)											//30,000 ms is 30 seconds
			{				
				LED_Matrix_Tick(LED_Matrix_cursor);								// gives control to matrix cursor // Joystick less sensitive this way
				if((LCD_counter % 100) == 0)									
				{
					Joystick_tick(Joystick_navigate);							// gives control to the joystick
					//LED_Matrix_Tick(LED_Matrix_cursor);						// gives control to matrix cursor
				}
				
				countdown = 30;													//countdown starts at 30 seconds
				if((LCD_counter % 1000) == 0)									//every second
				{
					itoa(countdown, snum, 10);									//turn countdown into decimal number 
					nokia_lcd_set_cursor(0, 0);
					nokia_lcd_write_string("Countdown: ", 1);
					nokia_lcd_set_cursor(0, 10);								
					nokia_lcd_write_string(snum, 1);							//print countdown
					nokia_lcd_render();
					countdown--;						
				}
				LCD_counter++;				
			}
			
			LCD_counter = 0;
			Nokia_LCD_State = Nokia_LCD_Compare;
			break;
		
		case Nokia_LCD_Compare:
			for(current_row = 0; current_row < 8; current_row++)				 
			{
				if(user_input[current_row] == levels[level-1][current_row])		//if the user_input array matches the level array 
				{
					row_is_correct += 1;										//for all of the 8 values in the array
				}
			}
			if(row_is_correct == 8)
			{
				score += 20;													//add 20 points to the score
			}
			
			nokia_lcd_set_cursor(0, 18);
			nokia_lcd_write_string("Press button to continue.", 1);				//want this to display until user gives input
			nokia_lcd_render();

			Nokia_LCD_State = Nokia_LCD_wait_before_level;						//go back to waiting before user gives an input before the next level
			break;
			
		default:
			Nokia_LCD_State = Nokia_LCD_Start;
			break;
	}
	
	switch(Nokia_LCD_State) //state actions
	{
		case Nokia_LCD_Start:
			break;
		case Nokia_LCD_wait_before_level:
			break;
		case Nokia_LCD_levels:
			LCD_display(level, score);			//display level and score
			//display the level image on the matrix for 10 seconds! HELP!
		
			//each level has a different picture which will display on the LED Matrix.
			// so depending on the level send output to the matrix state machine.
			break;
		case Nokia_LCD_Continue:
			break;
		case Nokia_LCD_Compare:
			//get the score by comparing matrices
			break;
		default:
			break;
	}
	
	//PORTC = output;
}	//end of Button LA function


#endif