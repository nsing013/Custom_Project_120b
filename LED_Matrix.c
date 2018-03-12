#ifndef __LED_MATRIX_c__
#define __LED_MATRIX_c__

//LEVEL 1
/*
11111111
11100111
11100111
11111111
11100111
11110111
11101111
11111111
*/
unsigned char y_1 [] = {0xFF, 0xE7, 0xE7, 0xFF, 0xE7, 0xF7, 0xEF, 0xFF};			//level 1 semicolon

//LEVEL 2
/*
11100111
11011011
10111101
01111110
01111110
10111101
11011011
11100111
*/
unsigned char y_2 [] = {0xE7, 0xDB, 0xBD, 0x7E, 0x7E, 0xBD, 0xDB, 0xE7};			//level 2 diamond
	
//LEVEL 3
/*
11000011
10111101
01011010
01111110
01011010
01100110
10111101
11000011
*/
unsigned char y_3 [] = {0xC3, 0xBD, 0x5A, 0x7E, 0x5A, 0x66, 0xBD, 0xC3};			//level 3 smiley
	
//LEVEL 4
/*
01010101
10101010
01010101
10101010
01010101
10101010
01010101
10101010
*/
unsigned char y_4 [] = {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA};			//level 4 Checkers

//LEVEL 5
/*
11111111
11111111
10011111
01101101
00001000
01101101
01101111
11111111
*/
unsigned char y_5 [] = {0xFF, 0xFF, 0x9F, 0x6D, 0x08, 0x6D, 0x6F, 0xFF};			//level 5 A+
	
unsigned char* levels[] = {y_1, y_2, y_3, y_4, y_5};									// array of all the levels

// CURSOR
/*
01111111
11111111
11111111
11111111
11111111
11111111
11111111
11111111
*/
short Matrix_counter;
unsigned char user_input [8] = {0x00};									// empty user input array, will hold positions user decides to light up
unsigned char row, col;													// row is the row number(the array), col is the bit in each row (the numbers in the array are 8 bits each) 
unsigned char cursor_x = 0x80;											// this is the column where the cursor is 
unsigned char cursor_y = 0x01;											// this is the row where the cursor is
unsigned char user_row_val = 0x00;		
unsigned char correct = 0x00;											//this variable works as a bool when comparing the user_input to the level array.  								
char i = 0;
extern char level; 

enum LED_Matrix_States {LED_Matrix_Start, LED_Matrix_levels, LED_Matrix_cursor, LED_Matrix_move_right, LED_Matrix_move_left, LED_Matrix_move_up, LED_Matrix_move_down, LED_Matrix_update_user_matrix};
int LED_Matrix_Tick(int state)
{
	switch (state)							//Transitions
	{
		case LED_Matrix_Start:				break;
		case LED_Matrix_levels:				break;
		case LED_Matrix_cursor:				break;
		case LED_Matrix_move_right:			break;
		case LED_Matrix_move_left:			break;
		case LED_Matrix_move_up:			break;
		case LED_Matrix_move_down:			break;
		case LED_Matrix_update_user_matrix: break;
		default:
			state = LED_Matrix_levels;
			break;
	}
	
	switch (state)							//Actions
	{
		case LED_Matrix_Start:
			break;
			
		case LED_Matrix_levels:				//don't screw with this
			PORTC = 0xFF;					//resets PORTC every time so last row does not mess with output for new row
			PORTD = 0x01 << i;				//increments to next row, shifting will send power to the next row with every loop
			PORTC = levels[level - 1][i];
			i++;
			if(i==8) {i = 0;}				//if at the end of row, restart at the start of next row
			break;
			
		case LED_Matrix_cursor:
			PORTC = 0xFF;								//Reset PortC every time so last row does not mess with output for new row
			PORTD = (0x01 << i);	
			if(i == row){								//if the cursor is in the current row
				PORTC = ~(user_input [i] | cursor_x);	//want to show the cursor with the user input, negated because we want to make a circuit
			}
			else{
				PORTC = ~(user_input [i]);				//or else just show the pattern for that row
			}	
			i++;
			if(i==8) {i = 0;} 
			break;
			
		case LED_Matrix_move_right:		
			if(col == 7)					//if at the right boundary
				break;						//do nothing
			col++;							
			cursor_x = (0x80 >> col);		//Shift the led at the very left by col (which is incremented every time LED_Matrix_move_right is called) So it will start from the 8th bit every time and shift backward.
			break;
			
		case LED_Matrix_move_left:
			if(col == 0)					//if at the right boundary
				break;						//do nothing
			col--;
			cursor_x = (0x80 >> col);		//still shifting right, but col is decremented every time LED_Matrix_move_left is called so we are shifting by less
			break;
			
		case LED_Matrix_move_up:
			if(row == 0)					//if at the top boundary
				break;						//do nothing
			row--;
			cursor_y = (0x01 << row);		//similar to x axis, shifting left because the 8 bits represent the row #, shifting left means moving down the rows
			break;
			
		case LED_Matrix_move_down:
			if(row == 7)
				break;
			row++;
			cursor_y = (0x01 << row);
			break;
			
		case LED_Matrix_update_user_matrix:	
			user_input[row] |= cursor_x;	//updates user_input array with the current cursor value
			user_row_val |= 0x01 << row;	//giving power to all the rows
			break;
			
		default:
			break;
	}
	return state;
};



#endif