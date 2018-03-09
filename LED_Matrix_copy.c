
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
unsigned char y1 [] = {0xFF, 0xE7, 0xE7, 0xFF, 0xE7, 0xF7, 0xEF, 0xFF};			//level 1 semicolon

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
unsigned char y2 [] = {0xE7, 0xDB, 0xBD, 0x7E, 0x7E, 0xBD, 0xDB, 0xE7};			//level 2 diamond
	
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
unsigned char y3 [] = {0xC3, 0xBD, 0x5A, 0x7E, 0x5A, 0x66, 0xBD, 0xC3};			//level 3 smiley
	
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
unsigned char y4 [] = {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA};			//level 4 Checkers

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
unsigned char y5 [] = {0xFF, 0xFF, 0x9F, 0x6D, 0x08, 0x6D, 0x6F, 0xFF};			//level 5 A+
	
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
//unsigned char y_cursor [] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};	//cursor starts at top left
unsigned char y_cursor [] = {0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	//cursor starts at top left
	
unsigned char user_input [8] = {0xFF}; //empty user input array, will hold positions user lights up
	
unsigned char row, col;

int i = 0;
enum LED_Matrix_States {LED_Matrix_Start, LED_Matrix_cursor, LED_Matrix_move_right, LED_Matrix_move_left, LED_Matrix_move_up, LED_Matrix_move_down, LED_Matrix_levels};
int LED_Matrix_Tick(int state)
{
	switch (state) //Transitions
	{
		case LED_Matrix_Start:
			break;
		case LED_Matrix_cursor:
			break;
		case LED_Matrix_move_right:
			break;
		case LED_Matrix_move_left:
			break;
		case LED_Matrix_move_up:
			break;
		case LED_Matrix_move_down:
			break;
		case LED_Matrix_levels:
			break;
		default:
			state = LED_Matrix_levels;
			break;
	}
	
	switch (state) //Actions
	{
		case LED_Matrix_Start:
			break;
		case LED_Matrix_cursor:
			PORTC = 0xFF;		//resets port c every time so last row does not mess with output for new row
			PORTC = y_cursor[i]; 
			PORTD = 0x01; //gives 1 to all rows
			//i++;
			//if(i==8) {i = 0;}	//if at the end of row, restart at the start of next row
			break;
		case LED_Matrix_move_right:		
			if(row == 7)
			{
				break;
			}
			row++;
			//if(y_cursor[i] == 0xFE)					//if you are at the right boundary of the matrix
			{
				//break;								//do nothing
			}
			//y_cursor[row] |=  
			i++;
			//if(i==8) {i = 0;}	//if at the end of row, restart at the start of next row
			//y_cursor[i] = ~(~(y_cursor[i])>>1);		//negate the number, shift it right, negate it again //update the cursor value
			//y_cursor[i] = 0xBF;
			//state = LED_Matrix_cursor;
			break;
		case LED_Matrix_move_left:
			if(y_cursor[i] == 0x7F)					//if you are at the left boundary of the matrix then do nothing
			{
				break;								//do nothing
			}	
			i--;
			//y_cursor[i] = ~(~(y_cursor[i])<<1);		//negate the number, shift it left, negate it again //update the cursor value
			//state = LED_Matrix_cursor;
			break;
		case LED_Matrix_move_up:
			break;
		case LED_Matrix_move_down:
			break;
		case LED_Matrix_levels:
			PORTC = 0xFF;		//resets port c every time so last row does not mess with output for new row
			PORTD = 0x01 << i;	//increments to next row
			PORTC = y5[i];		//lights up the pattern for the given row
			i++;
			if(i==8) {i = 0;}	//if at the end of row, restart at the start of next row
			break;
		default:
			break;
	}
	return state;
};

//LED MATRIX TEST CODE END


//Use two synchSMs. One synchSM controls the pattern displayed on the LED matrix. The other synchSM monitors button presses.




/*
enum Matrix_States {Matrix_Start, Matrix_wait, Matrix_Image, Matrix_User_Input, Matrix_Compare} Matrix_State;
void LED_Matrix_tick()
{
	int score = 0; //will be levelsed on the nokia LCD 
	switch(Matrix_State) //start transitions
	{
		case Matrix_Start:
			break;
		
		case Matrix_wait:
			//check level
			break;
		
		case Matrix_Image:
			//levels image for 10 seconds 
			break;
		
		case Matrix_User_Input:
			//allow LED_matrix to take input for 30 seconds
			//user uses joystick to navigate and presses joystick to light up current LED
			//store user input in a new matrix (probably a 2d array)
			break;
		
		case Matrix_Compare:
			//compare the user drawn image matrix to the original image matrix and give points for correct image
			//if(matrices match)
			// score +=20;
			//ask to continue and go to wait state.
			Matrix_State = Matrix_wait;
			break;
	
		default:
			Matrix_State = Matrix_Start;
			break;
	} //end of the transitions
	
	switch(Matrix_State) //state actions
	{
		case Matrix_Start:
			break;
		case Matrix_wait:
			break;
		case Matrix_Image:
			break;
		case Matrix_User_Input:
			break;
		case Matrix_Compare:
			break;
		default:
			break;
	}// end of the state actions
	
	PORTC = output;
} 
*/