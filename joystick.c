#ifndef __JOYSTICK_c__
#define __JOYSTICK_c__

// Using ADC to get the x and y axis of the JOYSTICK
void ADC_init() 
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are in Free Running Mode, a new conversion will trigger whenever the previous conversion completes.
}

unsigned short Read_ADC(uint8_t ch)
{
	ADMUX = (1<<REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2);
	ch = ch&0x07;
	ADMUX |= ch; //alternates between A0 and A1 which are the horizontal and vertical values on the joystick
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA |= (1<<ADIF);
	return ADC;
}

//PA[0] connected to potentiometer giving input //LEFT and RIGHT for joystick right now
//PA[1] want to connect to  y axis
unsigned short valueX, valueY;
unsigned short idle = 543;
unsigned short low_threshold = 510;		//250;
unsigned short high_threshold = 580;	//820;

enum Joystick_States {Joystick_navigate};

void Joystick_tick(int state) 
{
	short button = ~PINB & 0x20;							//button press also part of the joystick
	valueX = Read_ADC(1);									//getting x and y axis from joystick
	valueY = Read_ADC(0);
	
	switch(state) //start transitions
	{
		case Joystick_navigate:
			if(valueX < low_threshold)	{					//joystick is in the left position
				LED_Matrix_Tick(LED_Matrix_move_left);		//decrement x value on cursor
			}
			if(valueX > high_threshold)	{					//joystick is in the right position
				LED_Matrix_Tick(LED_Matrix_move_right);		//increment x value on cursor
			}
			if(valueY < low_threshold)	{					//joystick is in the left position
				LED_Matrix_Tick(LED_Matrix_move_up);		//increment x value on cursor, my joystick is sideways on the board so it has to be done this way
			}
			if(valueY > high_threshold)	{					//joystick is in the right position
				LED_Matrix_Tick(LED_Matrix_move_down);		//decrement x value on cursor
			}
			
			if(button)										// USE A BUTTON INSTEAD THERE IS NO BUTTON ON JOYSTICK DUMBB!
			{
				LED_Matrix_Tick(LED_Matrix_update_user_matrix); //update the user-input matrix 
				/* testing it on the nokia screen*/
				/*
				nokia_lcd_init();
				nokia_lcd_power(1);
				nokia_lcd_set_cursor(0, 0);
				nokia_lcd_write_string("Button is pressed!", 1);
				nokia_lcd_render();
				*/
			}
			state = Joystick_navigate;							//always stay in the navigate state
			break;
		
		default:
			state = Joystick_navigate;
			break;
	}
	
	switch(state) //state actions
	{
		case Joystick_navigate:
			break;
		default:
			break;
	}
}

#endif